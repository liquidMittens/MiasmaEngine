#include "app/GLWindow.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include "camera/Camera.h"
#include "rendering/GLRenderer.h"
#include "model/Scene.h"

GLWindow::GLWindow() :
	m_window(nullptr),
	m_cursor(nullptr)
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

	return result;
}

void GLWindow::ShutdownGLWindow()
{
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