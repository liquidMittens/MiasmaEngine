#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include <memory>
#include <string_view>
#include <filesystem>
#include <Miasma/core/rendering/GLRenderer.h>
#include <Miasma/core/rendering/GLRenderer2D.h>
using namespace Miasma::Renderer;
#include <Miasma/core/physics/PhysicsController.h>
#include <Miasma/core/glfw/glfw3.h>
using namespace Miasma::Physics;

constexpr std::string_view BUILD_VER = "MiasmaEngine v0.1.1";
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
	template<typename TScene, typename... Args>
	void ChangeScene(Args&&... args);

	const std::filesystem::path& EngineAssetRoot() { return assetRootDirectory; }
	const std::filesystem::path& EngineAssetTexureRoot() { return assetTexturesDirectory; }
	const std::filesystem::path& EngineAssetShaderRoot() { return assetShadersDirectory; }
	const std::filesystem::path& EngineAssetModelsRoot() { return assetModelsDirectory; }
	const std::filesystem::path& EngineAssetMaterialsRoot() { return assetMaterialsDirectory; }

private:
	std::unique_ptr<GLWindow> m_glWindow;
	std::unique_ptr<Miasma::Renderer::GLRenderer> m_renderer;
	std::unique_ptr<Miasma::Renderer::GLRenderer2D> m_renderer2D;
	static std::unique_ptr<IScene> m_currentScene;

	// bootstrap variables
	std::string assetRootDirectory;
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

	void calculateFrameRate();
	// engine bootstrapper method
	void loadEngineBootstrapConfig();
};

#endif