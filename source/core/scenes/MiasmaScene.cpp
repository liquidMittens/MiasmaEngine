#include "MiasmaScene.h"
#include "GameObject.h"
#include "Sprite2D.h"
#include "managers/TextureManager.h"
#include "Text.h"

MiasmaScene::MiasmaScene(SceneCreationInfo* creationInfo) :
	IScene(creationInfo)
{

}

MiasmaScene::~MiasmaScene()
{

}

void MiasmaScene::EnterScene()
{
	IScene::EnterScene();
	// create some objects
	Material playerMaterial;
	playerMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("borderedbackground"));
	playerMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));

	std::shared_ptr<GameObject> actionScreen = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> logScreen = std::make_shared<GameObject>();

	actionScreen->transform.translate(glm::vec2(IScene::m_screenSize.x * 0.5f, IScene::m_screenSize.y * 0.85f));
	actionScreen->AddComponent<Sprite2D>(actionScreen.get(), playerMaterial);
	actionScreen->GetComponent<Sprite2D>().SetSpriteSize(glm::vec2(IScene::m_screenSize.x, 200.0f));
	logScreen->transform.translate(glm::vec2(IScene::m_screenSize.x * 0.87f, IScene::m_screenSize.y * 0.5f));
	logScreen->AddComponent<Sprite2D>(logScreen.get(), playerMaterial);
	logScreen->GetComponent<Sprite2D>().SetSpriteSize(glm::vec2(IScene::m_screenSize.x * 0.25f, IScene::m_screenSize.y));

	std::shared_ptr<GameObject> text = std::make_shared<GameObject>();
	text->transform.translate(glm::vec2(IScene::m_screenSize.x * 0.87f, IScene::m_screenSize.y * 0.5f));
	text->AddComponent<Text>(text.get(), "This is a test log line.", glm::vec3(1.0f, 0.2f, 0.2f), 1.0f);

	m_gameObjectsList.push_back(actionScreen);
	m_gameObjectsList.push_back(logScreen);
	m_gameObjectsList.push_back(text);
}

void MiasmaScene::Update(float dt)
{
	IScene::Update(dt);
}

void MiasmaScene::ExitScene()
{
	IScene::ExitScene();
}

