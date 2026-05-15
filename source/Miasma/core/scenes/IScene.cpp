#include <Miasma/core/scenes/IScene.h>
#include <Miasma/core/app/GLWindow.h>
#include <Miasma/core/objects/GameObject.h>
#include <Miasma/core/app/Engine.h>
#include <iostream>

// TODO: change all scene creation info into bootstrap info?
IScene::IScene(SceneCreationInfo* creationInfo)
{
	m_glfwWindow = creationInfo->pWindow->GetGLFWWindow();
	m_screenSize.x = creationInfo->screenSize.x;
	m_screenSize.y = creationInfo->screenSize.y;
	m_camera = std::make_shared<GameObject>();
	// attach the camera component
	m_camera->AddComponent<tdogl::Camera>(m_camera.get());
	m_camera->tag = "MainCamera";
	m_camera->GetComponent<Camera>().initcamera(90.0f, 0.1f, 1000.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(m_screenSize.x, m_screenSize.y));
	m_gameObjectsList.push_back(m_camera);
}

void IScene::EnterScene(Engine* eng)
{
	// setup the assets for the scene
	m_shaderManager.LoadShaderList(eng->EngineAssetShaderRoot());
	TextureManager::GetInstance().LoadTexturesFromDirectory(eng->EngineAssetTexureRoot());
	m_sceneName = SCENE_TO_STRING(IScene);
}

void IScene::Update(float dt)
{
	// update all the gameobjects
	for (auto& gameobject : m_gameObjectsList) {
		// update components
		gameobject->UpdateGameObject(dt);
	}
}

void IScene::ExitScene()
{
	m_gameObjectsList.clear();
	m_lights.clear();
	m_camera.reset(); // reset the camera pointer since scene is shutting down
}