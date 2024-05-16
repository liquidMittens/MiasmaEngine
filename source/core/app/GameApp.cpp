#include "app/GameApp.h"
#include "app/GLWindow.h"
#include "model/IScene.h"
#include "model/SandboxScene.h"
#include "model/ChaosGameScene.h"
#include "model/MainScene.h"
#include "model/DoomScene.h"
#include <iostream>
#include <sstream>

std::unique_ptr<IScene> GameApp::m_currentScene = nullptr;

GameApp::GameApp() :
	m_lastTime(0.0),
	m_currentTime(0.0),
	m_numFrames(0),
	m_frameTime(0.0f),
	m_deltaTime(0.0),
	m_render2DMode(false),
	m_mouseModeEnabled(false)
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
		// create our scene and our GLRenderer
		SceneCreationInfo sceneInfo{ m_glWindow.get(), SCREEN_SIZE, false };
		m_render2DMode = sceneInfo.scene2dRenderer;
		m_currentScene = std::make_unique<DoomScene>(&sceneInfo);
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

void GameApp::ProcessInput()
{
	// quit application
	if (glfwGetKey(m_glWindow.get()->GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_glWindow.get()->GetGLFWWindow(), true);
	}

	// switch mouse modes
	if (glfwGetKey(m_glWindow.get()->GetGLFWWindow(), GLFW_KEY_TAB) == GLFW_PRESS) {
		glfwSetCursorPos(m_glWindow.get()->GetGLFWWindow(), 0, 0); //reset the mouse, so it doesn't go out of the window
		std::cout << "clicked TAB key\n";
		m_mouseModeEnabled = !m_mouseModeEnabled;
		if (m_mouseModeEnabled) {
			glfwSetInputMode(m_glWindow.get()->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(m_glWindow.get()->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
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
		// update scene and objects
		ProcessInput();
		PhysicsController::GetInstance().UpdatePhysicsSimulation((float)dt);
		m_currentScene->Update((float)dt);
		glfwPollEvents();
		// render and present
		if (m_render2DMode) {
			runWindowLoop = m_renderer2D->DrawScene(m_currentScene);
		}
		else {
			runWindowLoop = m_renderer->DrawScene(m_currentScene);
		}
		glfwSwapBuffers(m_glWindow->GetGLFWWindow());
		prevTime = currTime;
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