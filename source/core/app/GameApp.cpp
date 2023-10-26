#include "app/GameApp.h"
#include "app/GLWindow.h"
#include "core/model/Scene.h"
#include <iostream>
#include <sstream>

double GameApp::m_scrollY = 0.0;
bool GameApp::m_mouseModeEnabled = false;

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
		m_mouseModeEnabled = false;

		// create our scene and our GLRenderer
		SceneCreationInfo sceneInfo{ m_glWindow.get(), SCREEN_SIZE };
		m_currentScene = std::unique_ptr<Scene>(new Scene(&sceneInfo));
		m_currentScene->EnterScene();
		m_renderer = std::unique_ptr<Miasma::Renderer::GLRenderer>(new Miasma::Renderer::GLRenderer());
		m_renderer->Initialize(m_glWindow.get(), m_currentScene->GetCamera());
		m_renderer2D = std::make_unique<Miasma::Renderer::GLRenderer2D>();
		m_renderer2D->Initialize(m_glWindow.get(), m_currentScene->GetCamera());
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
		auto camera = m_currentScene->GetCamera();
		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(pWindow, true);
		}
		if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS) {
			m_wireframe = !m_wireframe;
		}
		//move position of camera based on WASD keys, and XZ keys for up and down
		if (glfwGetKey(pWindow, 'S')) {
			camera->offsetPosition(deltaTime * moveSpeed * -camera->forward());
		}
		else if (glfwGetKey(pWindow, 'W')) {
			camera->offsetPosition(deltaTime * moveSpeed * camera->forward());
		}
		if (glfwGetKey(pWindow, 'A')) {
			camera->offsetPosition(deltaTime * moveSpeed * -camera->right());
		}
		else if (glfwGetKey(pWindow, 'D')) {
			camera->offsetPosition(deltaTime * moveSpeed * camera->right());
		}
		if (glfwGetKey(pWindow, GLFW_KEY_LEFT_CONTROL)) {
			camera->offsetPosition(deltaTime * moveSpeed * -glm::vec3(0, 1, 0));
		}
		else if (glfwGetKey(pWindow, GLFW_KEY_SPACE)) {
			camera->offsetPosition(deltaTime * moveSpeed * glm::vec3(0, 1, 0));
		}

		if (!m_mouseModeEnabled) {
			//rotate camera based on mouse movement
			const float mouseSensitivity = 0.1f;
			double mouseX, mouseY;
			glfwGetCursorPos(pWindow, &mouseX, &mouseY);
			camera->offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
			glfwSetCursorPos(pWindow, 0, 0); //reset the mouse, so it doesn't go out of the window

			//increase or decrease field of view based on mouse wheel
			float fieldOfView = camera->fieldOfView() + zoomSensitivity * (float)m_scrollY;
			if (fieldOfView < 5.0f) fieldOfView = 5.0f;
			if (fieldOfView > 130.0f) fieldOfView = 130.0f;
			camera->setFieldOfView(fieldOfView);
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
	if (m_glWindow) {
		m_glWindow->ShutdownGLWindow();
	}
}