#include "model/MainScene.h"
#include "objects/GameObject.h"
#include "RigidBody2D.h"
#include "CollisionBody2D.h"
#include "Sprite2D.h"
#include "BoxCollider2D.h"


MainScene::MainScene(SceneCreationInfo* creationInfo) : 
	IScene(creationInfo)
{

}

MainScene::~MainScene()
{

}

void MainScene::EnterScene()
{
	IScene::EnterScene();

	// create some objects
	Material playerMaterial;
	playerMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("enemy"));
	playerMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));

	Material groundMaterial;
	groundMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("ground_0"));
	groundMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));

	std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> ground = std::make_shared<GameObject>();

	player->AddComponent<RigidBody2D>(player.get(), glm::vec2(960.0f, 500.0f));
	player->AddComponent<Sprite2D>(player.get(), playerMaterial);
	player->AddComponent<BoxCollider2D>(player.get());

	ground->AddComponent<CollisionBody2D>(ground.get(), glm::vec2(960.0f, 800.0f));
	ground->AddComponent<Sprite2D>(ground.get(), groundMaterial);
	ground->AddComponent<BoxCollider2D>(ground.get());

	m_gameObjectsList.push_back(player);
	m_gameObjectsList.push_back(ground);
}

void MainScene::Update(float dt)
{
	IScene::Update(dt);

}

void MainScene::ExitScene()
{
	IScene::ExitScene();

}