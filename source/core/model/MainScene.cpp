#include "model/MainScene.h"
#include "objects/GameObject.h"
#include "RigidBody2D.h"
#include "CollisionBody2D.h"
#include "Sprite2D.h"
#include "BoxCollider2D.h"
#include "AnimatedSprite2D.h"

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

	Material explosionMaterial;
	explosionMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("explosion"));
	explosionMaterial.AttachShader(m_shaderManager.GetShaderFromMap("AnimatedSprite"));

	std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> ground = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> animationObject = std::make_shared<GameObject>();

	std::shared_ptr<GameObject> explosion1 = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> explosion2 = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> explosion3 = std::make_shared<GameObject>();

	player->AddComponent<RigidBody2D>(player.get(), glm::vec2(960.0f, 500.0f));
	player->AddComponent<Sprite2D>(player.get(), playerMaterial);
	player->AddComponent<BoxCollider2D>(player.get());

	ground->AddComponent<CollisionBody2D>(ground.get(), glm::vec2(960.0f, 800.0f));
	ground->AddComponent<Sprite2D>(ground.get(), groundMaterial);
	ground->AddComponent<BoxCollider2D>(ground.get());

	AnimationCreateInfo2D explosionInfo;
	explosionInfo.animationTime = 0.05f;
	explosionInfo.frameSizeX = 4;
	explosionInfo.frameSizeY = 4;
	explosionInfo.loopAnimation = true;
	explosionInfo.material = explosionMaterial;
	animationObject->transform.translate(glm::vec3(900.0f, 300.0f, 1.0f));
	animationObject->AddComponent<AnimatedSprite2D>(animationObject.get(), explosionInfo);

	explosion1->transform.translate(glm::vec3(200.0f, 200.0f, 1.0f));
	explosion2->transform.translate(glm::vec3(800.0f, 800.0f, 1.0f));
	explosion3->transform.translate(glm::vec3(1500.0f, 100.0f, 1.0f));
	explosion1->AddComponent<AnimatedSprite2D>(explosion1.get(), explosionInfo);
	explosion2->AddComponent<AnimatedSprite2D>(explosion2.get(), explosionInfo);
	explosion3->AddComponent<AnimatedSprite2D>(explosion3.get(), explosionInfo);

	m_gameObjectsList.push_back(player);
	m_gameObjectsList.push_back(ground);
	m_gameObjectsList.push_back(animationObject);
	m_gameObjectsList.push_back(explosion1);
	m_gameObjectsList.push_back(explosion2);
	m_gameObjectsList.push_back(explosion3);
}

void MainScene::Update(float dt)
{
	IScene::Update(dt);

}

void MainScene::ExitScene()
{
	IScene::ExitScene();

}