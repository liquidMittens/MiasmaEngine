#include <Miasma/core/app/Engine.h>
#include <Miasma/core/app/GLWindow.h>
#include <Miasma/core/scenes/IScene.h>
#include <Miasma/core/scenes/SandboxScene.h>
#include <Miasma/core/scenes/ChaosGameScene.h>
#include <Miasma/core/scenes/MiasmaScene.h>
#include <Miasma/core/scenes/MainScene.h>
#include <Miasma/core/utility/toml.hpp>
#include <iostream>
#include <cerrno>
#include <sstream>
#include <vector>
#include <Miasma/core/utility/MiasmaLogger.hpp>
using namespace utility;
namespace fs = std::filesystem;

std::unique_ptr<IScene> Engine::m_currentScene = nullptr;

Engine::Engine() :
	m_sceneCreationInfo(nullptr),
	m_lastTime(0.0),
	m_currentTime(0.0),
	m_numFrames(0),
	m_frameTime(0.0f),
	m_deltaTime(0.0),
	m_render2DMode(false),
	m_mouseModeEnabled(false)
{

}

Engine::~Engine()
{

}

void Engine::InitializeGameEngine()
{
	// read the engine bootstrap file
	loadEngineBootstrapConfig();

	// create out window
	m_glWindow = std::unique_ptr<GLWindow>(new GLWindow());
	bool createWindowResult = m_glWindow->CreateGLWindow();
	if (createWindowResult) {
		// create our scene and our GLRenderer
		SceneCreationInfo sceneInfo{ m_glWindow.get(), SCREEN_SIZE, false, "resources\\textures\\", "resources\\shaders\\" };
		m_render2DMode = sceneInfo.scene2dRenderer;
		// init the scene registry
		sceneRegistry.CreateSceneRegistry(&sceneInfo);
		ChangeScene("MainScene");

		m_renderer = std::make_unique<Miasma::Renderer::GLRenderer>();
		m_renderer->Initialize(m_glWindow.get());
		m_renderer2D = std::make_unique<Miasma::Renderer::GLRenderer2D>();
		m_renderer2D->Initialize(m_glWindow.get());
	}
	else {
		MiasmaLogger::Log(LogLevel::Error, "m_glWindow->CreateGLWindow() Failed");
	}
}

void Engine::ProcessInput()
{
	// quit application
	if (glfwGetKey(m_glWindow.get()->GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_glWindow.get()->GetGLFWWindow(), true);
	}

	// switch mouse modes
	if (glfwGetKey(m_glWindow.get()->GetGLFWWindow(), GLFW_KEY_TAB) == GLFW_PRESS) {
		glfwSetCursorPos(m_glWindow.get()->GetGLFWWindow(), 0, 0); //reset the mouse, so it doesn't go out of the window

		m_mouseModeEnabled = !m_mouseModeEnabled;
		if (m_mouseModeEnabled) {
			glfwSetInputMode(m_glWindow.get()->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(m_glWindow.get()->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

}

void Engine::RunEngineLoop()
{
	bool runWindowLoop = true;
	if (runWindowLoop && !m_renderer) {
		MiasmaLogger::Log(LogLevel::Error, "GLRenderer is NULL leaving ExecuteGLWindowLoop!!");
		runWindowLoop = false;
	}
	if (runWindowLoop && !m_renderer2D) {
		MiasmaLogger::Log(LogLevel::Error, "GLRenderer2D is NULL leaving ExecuteGLWindowLoop!!");
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
		if (m_currentScene != nullptr)
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

void Engine::ShutdownEngine()
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

#pragma region ENGINE_SCENE_METHODS

void Engine::ChangeScene(std::string_view sceneName)
{
	if (m_currentScene)
		m_currentScene->ExitScene();

	m_currentScene = sceneRegistry.GetSceneFromRegistry(sceneName);
	if (m_currentScene) {
		m_currentScene->EnterScene(this);
		MiasmaLogger::Log(LogLevel::Info, "Loading Scene [{}]", m_currentScene->GetSceneName());
	}
}


template<typename TScene>
void Engine::RegisterScene(std::string sceneName)
{
	
}

#pragma endregion ENGINE_SCENE_METHODS

#pragma region PRIVATE_ENGINE_METHODS

void Engine::calculateFrameRate()
{
	m_currentTime = glfwGetTime();
	m_deltaTime = m_currentTime - m_lastTime;

	if (m_deltaTime >= 1) {
		int framerate{ std::max(1, int(m_numFrames / m_deltaTime)) };
		std::stringstream title;
		title << "MiasmaEngine (FPS: " << framerate << " )";
		glfwSetWindowTitle(m_glWindow->GetGLFWWindow(), title.str().c_str());
		m_lastTime = m_currentTime;
		m_numFrames = -1;
		m_frameTime = float(1000.0 / framerate);
	}
	++m_numFrames;
}

void Engine::loadEngineBootstrapConfig()
{
	toml::table bootstrapTable;
	try
	{
		bootstrapTable = toml::parse_file(BOOTSTRAP_CFG_FILE);
		// asset root directories loading
		auto assetsTable = bootstrapTable["assets"];
		assetTexturesDirectory = std::filesystem::path( assetsTable["assetTexturesRoot"].value_or("./resources/textures"));
		assetShadersDirectory = std::filesystem::path(assetsTable["assetShadersRoot"].value_or("./resources/shaders"));
		assetModelsDirectory = std::filesystem::path(assetsTable["assetModelsRoot"].value_or("./resources/models"));
		assetMaterialsDirectory = std::filesystem::path(assetsTable["assetMaterialsRoot"].value_or("./resources/materials"));
		validateEngineBootstrapConfig();

		// scene list loading
		auto sceneTable = bootstrapTable["scenes"];
		startUpSceneName = sceneTable["startup"].value_or("unnamed");
	}
	catch(const toml::parse_error& err)
	{
		MiasmaLogger::Log(LogLevel::Error, "Error loading {} - {}", BOOTSTRAP_CFG_FILE, err.description());
	}
}

void Engine::validateEngineBootstrapConfig()
{
	// check asset paths
	if (!fs::exists(assetTexturesDirectory))
		MiasmaLogger::Log(LogLevel::Error, "Textures asset directory doesnt exist!");
	if (!fs::exists(assetShadersDirectory))
		MiasmaLogger::Log(LogLevel::Error, "Shaders asset directory doesnt exist!");
	if (!fs::exists(assetModelsDirectory))
		MiasmaLogger::Log(LogLevel::Error, "Models asset directory doesnt exist!");
	if (!fs::exists(assetMaterialsDirectory))
		MiasmaLogger::Log(LogLevel::Error, "Materials asset directory doesnt exist!");

}

#pragma endregion PRIVATE_ENGINE_METHODS