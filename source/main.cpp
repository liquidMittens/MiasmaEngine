// main 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <vector>
#include <memory>
#include "camera/Camera.h"
#include "rendering/GLRenderer.h"
#include "model/Scene.h"
#include <sstream>

ShaderManager shaderManager;
// fps counter
double lastTime, currentTime;
int numFrames;
float frameTime;
double deltaTime;


GLFWwindow* InitWindow()
{
	bool result = true;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// GLFW_OPENGL_CORE_PROFILE - standard core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "OGLRenderer", NULL, NULL);
	if (pWindow == nullptr) {
		std::cout << "Failed to create GLFWwindow object!\n";
		glfwTerminate();
	}
	
	if (result) {
		glfwMakeContextCurrent(pWindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "GLAD initialize failed!";
			glfwTerminate();
		}
		if (result) {
			glViewport(0, 0, (int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y);
			glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(pWindow, 0, 0);
		} 
	}
	return pWindow;
}

void calculateFrameRate(GLFWwindow* pWindow) {
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;

	if (deltaTime >= 1) {
		int framerate{ std::max(1, int(numFrames / deltaTime)) };
		std::stringstream title;
		title << "OGLSandbox (FPS: " << framerate << " )";
		glfwSetWindowTitle(pWindow, title.str().c_str());
		lastTime = currentTime;
		numFrames = -1;
		frameTime = float(1000.0 / framerate);
	}
	++numFrames;
}

int main(int argc, char** argv)
{
	GLFWwindow* pWindow = InitWindow();
	SceneCreationInfo sceneCreationInfo = { pWindow, SCREEN_SIZE };
	std::unique_ptr<Scene> scene(new Scene(&sceneCreationInfo));
	scene->EnterScene();

	GLRenderer renderer;
	renderer.Initialize(scene->GetCamera());
	
	float prevTime = 0.0f;
	while (!glfwWindowShouldClose(pWindow)) {
		// calculate delta time per frame
		calculateFrameRate(pWindow);
		double currTime = (float)glfwGetTime();
		double dt = currTime - prevTime;
		scene->Update((float)dt);
		glfwPollEvents();
		renderer.DrawScene(scene);
		glfwSwapBuffers(pWindow);
		prevTime = currTime;
	}

	scene->ExitScene();
	renderer.Shutdown();
	glfwTerminate();
	return 0;
}