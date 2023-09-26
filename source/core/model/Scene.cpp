#include "model/Scene.h"
#include "objects/MeshRenderable.h"
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
	m_lights.push_back(std::unique_ptr<Light>(new Light(&lightCreation)));

	LightCreationInfo lightCreation2;
	lightCreation2.color = glm::vec3(0.0f, 1.0f, 0.0f);
	lightCreation2.pos = glm::vec3(-5.0f, 20.0f, -5.0f);
	lightCreation2.lightStrength = 30.0f;
	m_lights.push_back(std::unique_ptr<Light>(new Light(&lightCreation2)));
	
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
	std::shared_ptr<GameObject> catBlinnObject = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<GameObject> catDiffuseObject = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<GameObject> cottageObject = std::shared_ptr<GameObject>(new GameObject());


	// Setup MeshRenderable objects to be rendered
	catBlinnObject->AddComponent<miasma_rtti::MeshRenderable>(catBlinnObject.get(), &catMesh, textureBlinnMaterial);
	catBlinnObject->transform.GetTransform() = glm::mat4(1.0f);
	catBlinnObject->transform.GetTransform() = glm::translate(catBlinnObject->transform.GetTransform(), { 0.0f, 0.0f, 0.0f });
	catBlinnObject->transform.GetTransform() = glm::rotate(catBlinnObject->transform.GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	m_gameObjectsList.push_back(catBlinnObject);

	catMesh.meshName = "Cat Diffuse Outline";
	catDiffuseObject->AddComponent<miasma_rtti::MeshRenderable>(catDiffuseObject.get(), &catMesh, textureOutline);
	catDiffuseObject->transform.GetTransform() = glm::mat4(1.0f);
	catDiffuseObject->transform.GetTransform() = glm::translate(catDiffuseObject->transform.GetTransform(), { 10.0f, 0.0f, -5.0f });
	catDiffuseObject->transform.GetTransform() = glm::rotate(catDiffuseObject->transform.GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	catDiffuseObject->transform.SetPosition({ 10.0f, 0.0f, -5.0f });
	m_gameObjectsList.push_back(catDiffuseObject);

	///*std::shared_ptr<miasma_rtti::MeshRenderable> lightMesh(new miasma_rtti::MeshRenderable(nullptr, &lightTextureCreateInfo, redbasicTextureMaterial));
	//lightMesh->gameObject->transform.GetTransform() = glm::mat4(1.0f);
	//lightMesh->gameObject->transform.GetTransform() = glm::translate(lightMesh->gameObject->transform.GetTransform(), { lightCreation.pos });
	//m_meshRenderableList.push_back(lightMesh);

	//lightTextureCreateInfo.meshName = "Left Light Mesh";
	//std::shared_ptr<miasma_rtti::MeshRenderable> lightMesh2(new miasma_rtti::MeshRenderable(nullptr, &lightTextureCreateInfo, greenbasicTextureMaterial));
	//lightMesh2->gameObject->transform.GetTransform() = glm::mat4(1.0f);
	//lightMesh2->gameObject->transform.GetTransform() = glm::translate(lightMesh2->gameObject->transform.GetTransform(), { lightCreation2.pos });
	//m_meshRenderableList.push_back(lightMesh2);*/

	cottageObject->AddComponent<miasma_rtti::MeshRenderable>(cottageObject.get(), &cottageMeshCreateInfo, textureBlinnCottageMaterial);
	cottageObject->transform.GetTransform() = glm::mat4(1.0f);
	cottageObject->transform.GetTransform() = glm::translate(cottageObject->transform.GetTransform(), { 2.0f, 0.0f, -14.0f });
	m_gameObjectsList.push_back(cottageObject);
}

void Scene::Update(float dt)
{
	float angle = glm::radians<float>(10.0f * dt);
	for (auto& gameobject : m_gameObjectsList) {
		// update components
		gameobject->UpdateGameObject(dt);
	}
}

void Scene::ExitScene()
{

}