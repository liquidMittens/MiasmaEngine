#include "model/Scene.h"
#include "components/MeshRenderable.h"
#include "model/Cube.h"
#include "model/Rectangle.h"
#include "app/GLWindow.h"
#include "rendering/Texture2D.h"
#include "objects/GameObject.h"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "utility/MeshLoader.h"
#include "gui/GUIBuilder.h"
using namespace miasma_rtti;
 
Scene::Scene(SceneCreationInfo* creationInfo)
{
	m_glfwWindow = creationInfo->pWindow->GetGLFWWindow();
	m_screenSize.x = creationInfo->screenSize.x;
	m_screenSize.y = creationInfo->screenSize.y;
	m_camera = std::make_shared<tdogl::Camera>();
	m_camera->initcamera(90.0f, 0.1f, 100.0f, glm::vec3(0, 0, 14), glm::vec2(m_screenSize.x, m_screenSize.y));
}

Scene::~Scene()
{

}

void Scene::EnterScene()
{
	m_camera->initcamera(90.0f, 0.1f, 100.0f, glm::vec3(0, 3, 14), glm::vec2(m_screenSize.x, m_screenSize.y));
	m_shaderManager.LoadShaderList(SHADER_DIR);
	m_textureManager.LoadTexturesFromDirectory(TEXTURE_DIR);

	// Create using a MeshRenderable
	Material textureBlinnMaterial;
	textureBlinnMaterial.AddTexture(m_textureManager.GetTextureInfo("white"));
	textureBlinnMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// outline
	Material textureOutline;
	textureOutline.AddTexture(m_textureManager.GetTextureInfo("cat"));
	textureOutline.AttachShader(m_shaderManager.GetShaderFromMap("TextureOutline"));
	// green
	Material greenbasicTextureMaterial;
	greenbasicTextureMaterial.AddTexture(m_textureManager.GetTextureInfo("green"));
	greenbasicTextureMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicTexture"));
	// red
	Material redbasicTextureMaterial;
	redbasicTextureMaterial.AddTexture(m_textureManager.GetTextureInfo("red"));
	redbasicTextureMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BasicTexture"));
	// cottage Blinn
	Material textureBlinnCottageMaterial;
	textureBlinnCottageMaterial.AddTexture(m_textureManager.GetTextureInfo("cottage"));
	textureBlinnCottageMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));

	// Setup lights 
	// create lights
	LightCreationInfo lightCreation;
	lightCreation.color = glm::vec3(1.0f, 0.0f, 0.0f);
	lightCreation.pos = glm::vec3(4.0f, 8.0f, -6.0f);
	lightCreation.lightStrength = 10.0f;
	std::shared_ptr<GameObject> lightObject1 = std::make_shared<GameObject>();
	lightObject1->AddComponent<PointLight>(lightObject1.get(), &lightCreation);
	m_lights.push_back(lightObject1);

	LightCreationInfo lightCreation2;
	lightCreation2.color = glm::vec3(0.0f, 1.0f, 0.0f);
	lightCreation2.pos = glm::vec3(-5.0f, 20.0f, -5.0f);
	lightCreation2.lightStrength = 30.0f;
	std::shared_ptr<GameObject> lightObject2 = std::make_shared<GameObject>();
	lightObject2->AddComponent<PointLight>(lightObject2.get(), &lightCreation2);
	m_lights.push_back(lightObject2);

	
	// load two meshes
	miasma_rtti::MeshRenderableCreateInfo catMesh;
	catMesh.filename = "cat.obj";
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

	// make 4 GameObjects
	std::shared_ptr<GameObject> catBlinnObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> catDiffuseObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> cottageObject = std::make_shared<GameObject>();


	// Setup MeshRenderable objects to be rendered
	catBlinnObject->tag = "CatBlinnObject";
	catBlinnObject->AddComponent<miasma_rtti::MeshRenderable>(catBlinnObject.get(), &catMesh, textureBlinnMaterial);
	catBlinnObject->transform.GetTransform() = glm::mat4(1.0f);
	catBlinnObject->transform.GetTransform() = glm::translate(catBlinnObject->transform.GetTransform(), { 0.0f, 0.0f, 0.0f });
	catBlinnObject->transform.GetTransform() = glm::rotate(catBlinnObject->transform.GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	m_gameObjectsList.push_back(catBlinnObject);

	catMesh.meshName = "Cat Diffuse Outline";
	catDiffuseObject->tag = "CatDiffuseObject";
	catDiffuseObject->AddComponent<miasma_rtti::MeshRenderable>(catDiffuseObject.get(), &catMesh, textureOutline);
	catDiffuseObject->transform.GetTransform() = glm::mat4(1.0f);
	catDiffuseObject->transform.GetTransform() = glm::translate(catDiffuseObject->transform.GetTransform(), { 10.0f, 0.0f, -5.0f });
	catDiffuseObject->transform.GetTransform() = glm::rotate(catDiffuseObject->transform.GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	catDiffuseObject->transform.SetPosition({ 10.0f, 0.0f, -5.0f });
	m_gameObjectsList.push_back(catDiffuseObject);

	lightObject1->tag = "RedLightObject";
	lightObject1->AddComponent<miasma_rtti::MeshRenderable>(lightObject1.get(), &lightTextureCreateInfo, redbasicTextureMaterial);
	lightObject1->transform.GetTransform() = glm::mat4(1.0f);
	lightObject1->transform.GetTransform() = glm::translate(lightObject1->transform.GetTransform(), { lightCreation.pos });
	m_gameObjectsList.push_back(lightObject1);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	lightObject2->tag = "GreenLightObject";
	lightObject2->AddComponent<miasma_rtti::MeshRenderable>(lightObject2.get(), &lightTextureCreateInfo, greenbasicTextureMaterial);
	lightObject2->transform.GetTransform() = glm::mat4(1.0f);
	lightObject2->transform.GetTransform() = glm::translate(lightObject2->transform.GetTransform(), { lightCreation2.pos });
	m_gameObjectsList.push_back(lightObject2);

	cottageObject->tag = "CottageObject"; 
	cottageObject->AddComponent<miasma_rtti::MeshRenderable>(cottageObject.get(), &cottageMeshCreateInfo, textureBlinnCottageMaterial);
	cottageObject->transform.GetTransform() = glm::mat4(1.0f);
	cottageObject->transform.GetTransform() = glm::translate(cottageObject->transform.GetTransform(), { 2.0f, 0.0f, -14.0f });
	m_gameObjectsList.push_back(cottageObject);
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