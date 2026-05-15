#ifndef SCENEREGISTRY_H_
#define SCENEREGISTRY_H_
#include<unordered_map>
#include <string>
#include <string_view>
#include <memory>
#include <optional>
#include <Miasma/core/scenes/IScene.h>
#include <Miasma/core/scenes/MainScene.h>
#include <Miasma/core/scenes/MiasmaScene.h>
#include <Miasma/core/scenes/SandboxScene.h>
#include <Miasma/core/scenes/ChaosGameScene.h>


class SceneRegistry
{
public:

	/// <summary>
	/// This is a method that needs to be filled out that creates the mapping of available scenes.
	/// They key is the scene name and the value is a method that returns the unique_ptr of that scene class to be
	/// fed into the Engine to transition to.
	/// </summary>
	void CreateSceneRegistry(SceneCreationInfo* info)
	{
		registeredSceneMap["MainScene"] = [info]() -> std::unique_ptr<IScene> {
			return std::make_unique<MainScene>(info);
			};

		registeredSceneMap["MiasmaScene"] = [info]() -> std::unique_ptr<IScene> {
			return std::make_unique<MiasmaScene>(info);
			};

		registeredSceneMap["SandboxScene"] = [info]() -> std::unique_ptr<IScene> {
			return std::make_unique<SandboxScene>(info);
			};
	}

	std::unique_ptr<IScene> GetSceneFromRegistry(std::string_view scene)
	{
		auto sceneIter = registeredSceneMap.find(scene.data());
		if (sceneIter != registeredSceneMap.end()) {
			
			return sceneIter->second();
		}
		return nullptr;
	}

private:
	// scene list
	std::unordered_map <std::string, std::function<std::unique_ptr<IScene>()>> registeredSceneMap;
};

#endif