#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include <memory>
#include <string_view>
#include <filesystem>
#include <unordered_set>
#include <Miasma/core/scenes/SceneRegistry.hpp>
#include <Miasma/core/rendering/GLRenderer.h>
#include <Miasma/core/rendering/GLRenderer2D.h>
using namespace Miasma::Renderer;
#include <Miasma/core/physics/PhysicsController.h>
#include <Miasma/core/glfw/glfw3.h>
using namespace Miasma::Physics;
#include <Miasma/core/events/event.hpp>

constexpr std::string_view BUILD_VER = "MiasmaEngine v0.2.0";
// bootstrap config location for now
const std::filesystem::path ENGINE_DEFAULT_ROOT = "./resources";
constexpr auto BOOTSTRAP_CFG_FILE = ".\\engine.toml";

struct GLFWwindow;
class GLWindow;
class IScene;

class Engine
{
public:
	Engine();
	~Engine();

	void InitializeGameEngine();
	void ProcessInput();
	void RunEngineLoop();
	void ShutdownEngine();

	// Scene Methods
	void ChangeScene(std::string_view sceneName);
	template<typename TScene>
	void RegisterScene(std::string sceneName);

	const std::filesystem::path& EngineAssetRoot() { return assetRootDirectory; }
	const std::filesystem::path& EngineAssetTexureRoot() { return assetTexturesDirectory; }
	const std::filesystem::path& EngineAssetShaderRoot() { return assetShadersDirectory; }
	const std::filesystem::path& EngineAssetModelsRoot() { return assetModelsDirectory; }
	const std::filesystem::path& EngineAssetMaterialsRoot() { return assetMaterialsDirectory; }

#pragma region SCENE_EVENTS
	/// <summary>
	/// Event that fires when a new Scene is loaded.
	/// </summary>
	pulse::Event<std::string> onSceneLoadedEvent;

#pragma endregion SCENE_EVENTS

private:
	std::unique_ptr<GLWindow> m_glWindow;
	std::unique_ptr<SceneCreationInfo> m_sceneCreationInfo;
	std::unique_ptr<Miasma::Renderer::GLRenderer> m_renderer;
	std::unique_ptr<Miasma::Renderer::GLRenderer2D> m_renderer2D;
	static std::unique_ptr<IScene> m_currentScene;

	// bootstrap variables
	std::string assetRootDirectory;
	std::string startUpSceneName;
	// asset variables
	std::filesystem::path assetTexturesDirectory;
	std::filesystem::path assetShadersDirectory;
	std::filesystem::path assetModelsDirectory;
	std::filesystem::path assetMaterialsDirectory;

	// variables for calculating framerate
	// fps counter
	double m_lastTime, m_currentTime;
	int m_numFrames;
	float m_frameTime;
	double m_deltaTime;
	bool m_render2DMode;
	bool m_mouseModeEnabled;
	
	// scene registry
	SceneRegistry sceneRegistry;

	void calculateFrameRate();
	// engine bootstrapper method
	void loadEngineBootstrapConfig();
	// validate method for engine toml file
	void validateEngineBootstrapConfig();
};

#endif