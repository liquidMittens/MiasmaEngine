#include "app/GameApp.h"
#include "app/GLWindow.h"
#include "core/model/Scene.h"
#include <iostream>
#include <sstream>

double GameApp::m_scrollY = 0.0;
bool GameApp::m_mouseModeEnabled = false;
std::unique_ptr<Scene> GameApp::m_currentScene = nullptr;

GameApp::GameApp() :
	m_lastTime(0.0),
	m_currentTime(0.0),
	m_numFrames(0),
	m_frameTime(0.0f),
	m_deltaTime(0.0),
	m_wireframe(false)
{

}

GameApp::~GameApp()
{

}

void GameApp::InitializeGameApp()
{
	// create out window
	m_glWindow = std::unique_ptr<GLWindow>(new GLWindow());
	bool createWindowResult = m_glWindow->CreateGLWindow();
	if (createWindowResult) {
		// register callbacks 
		glfwSetScrollCallback(m_glWindow->GetGLFWWindow(), GameApp::OnScroll);
		glfwSetMouseButtonCallback(m_glWindow->GetGLFWWindow(), GameApp::OnMouseButton);
		glfwSetKeyCallback(m_glWindow->GetGLFWWindow(), GameApp::key_callback);
		m_mouseModeEnabled = false;
		// create our scene and our GLRenderer
		SceneCreationInfo sceneInfo{ m_glWindow.get(), SCREEN_SIZE };
		m_currentScene = std::make_unique<Scene>(&sceneInfo);
		m_currentScene->EnterScene();
		m_renderer = std::make_unique<Miasma::Renderer::GLRenderer>();
		m_renderer->Initialize(m_glWindow.get());
		m_renderer2D = std::make_unique<Miasma::Renderer::GLRenderer2D>();
		m_renderer2D->Initialize(m_glWindow.get());
	}
	else {
		std::cout << "m_glWindow->CreateGLWindow() Failed\n";
	}
}

void GameApp::RunGameAppLoop()
{
	bool runWindowLoop = true;
	if (!m_currentScene) {
		std::cout << "Scene Object is NULL leaving ExecuteGLWindowLoop!!\n";
		runWindowLoop = false;
	}
	if (runWindowLoop && !m_renderer) {
		std::cout << "GLRenderer is NULL leaving ExecuteGLWindowLoop!!\n";
		runWindowLoop = false;
	}
	if (runWindowLoop && !m_renderer2D) {
		std::cout << "GLRenderer2D is NULL leaving ExecuteGLWindowLoop!!\n";
		runWindowLoop = false;
	}

	double prevTime = 0.0;
	while (runWindowLoop && !glfwWindowShouldClose(m_glWindow->GetGLFWWindow())) {
		// calculate delta time per frame
		calculateFrameRate();
		double currTime = (float)glfwGetTime();
		double dt = currTime - prevTime;
		// get input
		ProcessInput(m_glWindow->GetGLFWWindow(), (float)dt);
		// update scene and objects
		PhysicsController::GetInstance().UpdatePhysicsSimulation((float)dt);
		m_currentScene->Update((float)dt);
		glfwPollEvents();
		// render and present
		runWindowLoop = m_renderer->DrawScene(m_currentScene);
		if (runWindowLoop) {
			runWindowLoop = m_renderer2D->DrawScene(m_currentScene);
		}
		glfwSwapBuffers(m_glWindow->GetGLFWWindow());
		prevTime = currTime;
	}
}

void GameApp::ProcessInput(GLFWwindow* pWindow, float deltaTime)
{
	if (pWindow != nullptr) {
		bool isAnyMovementPressed = false;
		auto& camera = m_currentScene->GetCamera()->GetComponent<Camera>();
		RigidBody& cameraBody = m_currentScene->GetCamera()->GetComponent<RigidBody>();

		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(pWindow, true);
		}
		if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS) {
			m_wireframe = !m_wireframe;
		}

		glm::vec3 velocity(0.0f, 0.0f, 0.0f);
		//move position of camera based on WASD keys, and XZ keys for up and down
		if (glfwGetKey(pWindow, GLFW_KEY_W)) {
			velocity.z += 1;
		}
		if (glfwGetKey(pWindow, GLFW_KEY_A)) {
			velocity.x -= 1;
		}
		if (glfwGetKey(pWindow, GLFW_KEY_S)) {
			velocity.z -= 1;
		}
		if (glfwGetKey(pWindow, GLFW_KEY_D)) {
			velocity.x += 1;
		}

		if (velocity.x != 0.0f || velocity.z != 0.0f) {
			glm::vec3 normalizedVelocity = glm::normalize(velocity);
			glm::vec3 relativeDirection = (normalizedVelocity.z * camera.forward_novertical_axis() + normalizedVelocity.x * camera.right());
			velocity.x = relativeDirection.x * moveSpeed;
			velocity.z = relativeDirection.z * moveSpeed;
			cameraBody.ApplyForce(rp3d::Vector3(velocity.x, 0.0, velocity.z));
		}

		if (glfwGetKey(pWindow, GLFW_KEY_LEFT_CONTROL)) {
			camera.offsetPosition(deltaTime * moveSpeed * -glm::vec3(0, 1, 0));
		}

		if (!m_mouseModeEnabled) {
			//rotate camera based on mouse movement
			const float mouseSensitivity = 0.1f;
			double mouseX, mouseY;
			glfwGetCursorPos(pWindow, &mouseX, &mouseY);
			camera.offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
			glfwSetCursorPos(pWindow, 0, 0); //reset the mouse, so it doesn't go out of the window

			//increase or decrease field of view based on mouse wheel
			float fieldOfView = camera.fieldOfView() + zoomSensitivity * (float)m_scrollY;
			if (fieldOfView < 5.0f) fieldOfView = 5.0f;
			if (fieldOfView > 130.0f) fieldOfView = 130.0f;
			camera.setFieldOfView(fieldOfView);
			m_scrollY = 0;
		}
	}
}

// records how far the y axis has been scrolled
void GameApp::OnScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	m_scrollY += deltaY;
}

void GameApp::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
		std::cout << "clicked mouse button right\n";
		m_mouseModeEnabled = !m_mouseModeEnabled;
		if (m_mouseModeEnabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}

void GameApp::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		auto& camera = m_currentScene->GetCamera()->GetComponent<Camera>();
		RigidBody& cameraBody = m_currentScene->GetCamera()->GetComponent<RigidBody>();
		rp3d::Vector3 jumpForceVec = jumpForce * rp3d::Vector3(0.0f, camera.up_novertical_axis().y, 0.0f);
		cameraBody.ApplyForce(jumpForceVec);
	}
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
		std::cout << "clicked TAB key\n";
		m_mouseModeEnabled = !m_mouseModeEnabled;
		if (m_mouseModeEnabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}

void GameApp::calculateFrameRate()
{
	m_currentTime = glfwGetTime();
	m_deltaTime = m_currentTime - m_lastTime;

	if (m_deltaTime >= 1) {
		int framerate{ std::max(1, int(m_numFrames / m_deltaTime)) };
		std::stringstream title;
		title << "OGLSandbox (FPS: " << framerate << " )";
		glfwSetWindowTitle(m_glWindow->GetGLFWWindow(), title.str().c_str());
		m_lastTime = m_currentTime;
		m_numFrames = -1;
		m_frameTime = float(1000.0 / framerate);
	}
	++m_numFrames;
}

void GameApp::ShutdownGameApp()
{
	if (m_currentScene) {
		m_currentScene->ExitScene();
	}
	if (m_renderer) {
		m_renderer->Shutdown();
	}
	if (m_renderer2D) {
		m_renderer2D->Shutdown();
	}
	PhysicsController::GetInstance().ShutdownPhysicsController();
	if (m_glWindow) {
		m_glWindow->ShutdownGLWindow();
	}
}