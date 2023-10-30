#include "model/Scene.h"
#include "app/GLWindow.h"
#include "components/MeshRenderable.h"
#include "components/SpinObject.h"
#include "components/Sprite2D.h"
#include "rendering/Texture2D.h"
#include "objects/GameObject.h"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "utility/MeshLoader.h"
#include "gui/GUIBuilder.h"
using namespace Miasma::RTTI;
 
Scene::Scene(SceneCreationInfo* creationInfo)
{
	m_glfwWindow = creationInfo->pWindow->GetGLFWWindow();
	m_screenSize.x = creationInfo->screenSize.x;
	m_screenSize.y = creationInfo->screenSize.y;
	m_camera = std::make_shared<tdogl::Camera>();
}

Scene::~Scene()
{

}

void Scene::EnterScene()
{
	m_camera->initcamera(90.0f, 0.1f, 1000.0f, glm::vec3(0, 3, 14), glm::vec2(m_screenSize.x, m_screenSize.y));
	m_shaderManager.LoadShaderList(SHADER_DIR);
	TextureManager::GetInstance().LoadTexturesFromDirectory(TEXTURE_DIR);

	// Create using a MeshRenderable
	Material textureBlinnMaterial;
	textureBlinnMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("white"));
	textureBlinnMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// outline
	Material textureOutline;
	textureOutline.AddTexture(TextureManager::GetInstance().GetTextureInfo("cat"));
	textureOutline.AttachShader(m_shaderManager.GetShaderFromMap("TextureOutline"));
	// green
	Material greenbasicTextureMaterial;
	greenbasicTextureMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("green"));
	greenbasicTextureMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicTexture"));
	// red
	Material redbasicTextureMaterial;
	redbasicTextureMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("red"));
	redbasicTextureMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicTexture"));
	// cottage Blinn
	Material textureBlinnCottageMaterial;
	textureBlinnCottageMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("cottage"));
	textureBlinnCottageMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// crate texture 
	Material crateMaterial;
	crateMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("crate1"));
	crateMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// create UI material
	Material spriteMaterial;
	spriteMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("reticle"));
	spriteMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));

	// Setup lights 
	// create lights
	LightCreationInfo lightCreation;
	lightCreation.color = glm::vec3(1.0f, 0.0f, 0.0f);
	lightCreation.pos = glm::vec3(4.0f, 8.0f, -6.0f);
	lightCreation.lightStrength = 40.0f;
	std::shared_ptr<GameObject> lightObject1 = std::make_shared<GameObject>();
	lightObject1->AddComponent<PointLight>(lightObject1.get(), &lightCreation);
	m_lights.push_back(lightObject1);

	LightCreationInfo lightCreation2;
	lightCreation2.color = glm::vec3(0.0f, 1.0f, 0.0f);
	lightCreation2.pos = glm::vec3(-5.0f, 8.0f, -5.0f);
	lightCreation2.lightStrength = 30.0f;
	std::shared_ptr<GameObject> lightObject2 = std::make_shared<GameObject>();
	lightObject2->AddComponent<PointLight>(lightObject2.get(), &lightCreation2);
	m_lights.push_back(lightObject2);

	
	// load two meshes
	Miasma::RTTI::MeshRenderableCreateInfo catMesh;
	catMesh.filename = "catnormal.obj";
	catMesh.preTransform = 0.1f * glm::mat4(1.0f);
	catMesh.meshName = "cat blinn";
	MeshRenderableCreateInfo lightTextureCreateInfo;
	lightTextureCreateInfo.filename = "cube.obj";
	lightTextureCreateInfo.preTransform = 0.05f * glm::mat4(1.0f);
	lightTextureCreateInfo.meshName = "Light Mesh";
	MeshRenderableCreateInfo cottageMeshCreateInfo;
	cottageMeshCreateInfo.filename = "cottage.obj";
	cottageMeshCreateInfo.preTransform = 0.5f * glm::mat4(1.0f);
	cottageMeshCreateInfo.meshName = "Cottage Mesh";
	// load cube mesh
	MeshRenderableCreateInfo crateMeshInfo;
	crateMeshInfo.filename = "Crate1.obj";
	crateMeshInfo.preTransform = glm::mat4(1.0f);
	crateMeshInfo.meshName = "Crate Mesh";
	// load a quad
	MeshRenderableCreateInfo quadMeshInfo;
	quadMeshInfo.filename = "QuadTest";
	quadMeshInfo.preTransform = glm::identity<glm::mat4>();
	quadMeshInfo.meshName = "QuadTest";

	// make 4 GameObjects
	std::shared_ptr<GameObject> catBlinnObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> catDiffuseObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> cottageObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> crateObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> quadObject = std::make_shared<GameObject>();


	// Setup MeshRenderable objects to be rendered
	catBlinnObject->tag = "CatBlinnObject";
	catBlinnObject->AddComponent<Miasma::RTTI::MeshRenderable>(catBlinnObject.get(), &catMesh, textureBlinnMaterial);
	catBlinnObject->AddComponent<Miasma::RTTI::SpinObject>(catBlinnObject.get(), 2.0f);
	catBlinnObject->transform.translate({ 0.0f, 0.0f, 0.0f });
	catBlinnObject->GetComponent<SpinObject>().Start();
	m_gameObjectsList.push_back(catBlinnObject);

	catMesh.meshName = "Cat Diffuse Outline";
	catDiffuseObject->tag = "CatDiffuseObject";
	catDiffuseObject->AddComponent<Miasma::RTTI::MeshRenderable>(catDiffuseObject.get(), &catMesh, textureOutline);
	catDiffuseObject->transform.translate({ 10.0f, 0.0f, -5.0f });
	m_gameObjectsList.push_back(catDiffuseObject);

	lightObject1->tag = "RedLightObject";
	lightObject1->AddComponent<Miasma::RTTI::MeshRenderable>(lightObject1.get(), &lightTextureCreateInfo, redbasicTextureMaterial);
	lightObject1->transform.translate({ lightCreation.pos });
	m_gameObjectsList.push_back(lightObject1);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	lightObject2->tag = "GreenLightObject";
	lightObject2->AddComponent<Miasma::RTTI::MeshRenderable>(lightObject2.get(), &lightTextureCreateInfo, greenbasicTextureMaterial);
	lightObject2->transform.translate({ lightCreation2.pos });
	m_gameObjectsList.push_back(lightObject2);

	cottageObject->tag = "CottageObject"; 
	cottageObject->AddComponent<Miasma::RTTI::MeshRenderable>(cottageObject.get(), &cottageMeshCreateInfo, textureBlinnCottageMaterial);
	cottageObject->transform.translate({ 2.0f, 0.0f, -14.0f });
	m_gameObjectsList.push_back(cottageObject);

	crateObject->tag = "CrateObject";
	crateObject->AddComponent<Miasma::RTTI::MeshRenderable>(crateObject.get(), &crateMeshInfo, crateMaterial);
	crateObject->transform.translate({4.0f, 1.0f, -7.0f});
	m_gameObjectsList.push_back(crateObject);

	quadObject->tag = "QuadObject";
	quadObject->transform = glm::translate(quadObject->transform.GetTransform(), {960.0f, 540.0f, 1.0f });
	quadObject->AddComponent<Miasma::RTTI::Sprite2D>(quadObject.get(), spriteMaterial);
	m_gameObjectsList.push_back(quadObject);
}

void Scene::Update(float dt)
{
	for (auto& gameobject : m_gameObjectsList) {
		// update components
		gameobject->UpdateGameObject(dt);
	}
}

void Scene::ExitScene()
{
	m_gameObjectsList.clear();
	m_lights.clear();
}