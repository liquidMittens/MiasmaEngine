#include "app/GLWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <sstream>
#include "camera/Camera.h"
#include "rendering/GLRenderer.h"
#include "model/Scene.h"

GLWindow::GLWindow() :
	m_lastTime(0.0),
	m_currentTime(0.0),
	m_numFrames(0),
	m_frameTime(0.0f),
	m_deltaTime(0.0)
{

}

GLWindow::~GLWindow()
{

}

bool GLWindow::CreateGLWindow()
{
	bool result = true;
	if (!InitGLWindow()) {
		std::cout << "Failed to create GLWindow!\n";
		result = false;
	}
	if (!InitGLFWCursor()) {
		std::cout << "Failed to create GLFWcursor!\n";
		result = false;
	}

	// create our scene and our GLRenderer
	SceneCreationInfo sceneInfo{ m_window, SCREEN_SIZE };
	m_scene = std::unique_ptr<Scene>(new Scene(&sceneInfo));
	m_scene->EnterScene();
	m_renderer = std::unique_ptr<GLRenderer>(new GLRenderer());
	m_renderer->Initialize(m_window, m_scene->GetCamera());

	return result;
}

void GLWindow::ExecuteGLWindowLoop()
{
	bool runLoop = true;
	if (!m_scene) {
		std::cout << "Scene Object is NULL leaving ExecuteGLWindowLoop!!\n";
		runLoop = false;
	}
	if (runLoop) {
		if (!m_renderer) {
			std::cout << "GLRenderer is NULL leaving ExecuteGLWindowLoop!!\n";
			runLoop = false;
		}
	}

	float prevTime = 0.0f;
	while (runLoop && !glfwWindowShouldClose(m_window)) {
		// calculate delta time per frame
		calculateFrameRate();
		double currTime = (float)glfwGetTime();
		double dt = currTime - prevTime;
		m_scene->Update((float)dt);
		glfwPollEvents();
		m_renderer->DrawScene(m_scene);
		glfwSwapBuffers(m_window);
		prevTime = currTime;
	}
}

void GLWindow::ShutdownGLWindow()
{
	if (m_scene) {
		m_scene->ExitScene();
	}
	if (m_renderer) {
		m_renderer->Shutdown();
	}
	glfwTerminate();
}

bool GLWindow::InitGLWindow()
{
	bool result = true;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// GLFW_OPENGL_CORE_PROFILE - standard core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "GLRenderer", NULL, NULL);
	if (m_window == nullptr) {
		std::cout << "Failed to create GLFWwindow object!\n";
		glfwTerminate();
	}

	if (result) {
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "GLAD initialize failed!";
			glfwTerminate();
		}
		if (result) {
			glViewport(0, 0, (int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y);
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			glfwSetCursorPos(m_window, 0, 0);
		}
	}
	return result;
}

void GLWindow::calculateFrameRate()
{
	m_currentTime = glfwGetTime();
	m_deltaTime = m_currentTime - m_lastTime;

	if (m_deltaTime >= 1) {
		int framerate{ std::max(1, int(m_numFrames / m_deltaTime)) };
		std::stringstream title;
		title << "OGLSandbox (FPS: " << framerate << " )";
		glfwSetWindowTitle(m_window, title.str().c_str());
		m_lastTime = m_currentTime;
		m_numFrames = -1;
		m_frameTime = float(1000.0 / framerate);
	}
	++m_numFrames;
}

bool GLWindow::InitGLFWCursor()
{
	bool result = true;
	if (m_window != nullptr) {
		m_cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		if (m_cursor != nullptr) {
			glfwSetCursor(m_window, m_cursor);
		}
		else {
			result = false;
		}
	}
	else {
		result = false;
	}
	return result;
}