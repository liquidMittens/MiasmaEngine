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
	m_camera->initcamera(45.0f, 0.1f, 1000.0f, glm::vec3(0, 3, 14), glm::vec2(m_screenSize.x, m_screenSize.y));
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
	// crate texture 
	Material crateMaterial;
	crateMaterial.AddTexture(m_textureManager.GetTextureInfo("crate1"));
	crateMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// create UI material
	Material spriteMaterial;
	spriteMaterial.AddTexture(m_textureManager.GetTextureInfo("missing"));
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
	catBlinnObject->transform.GetTransform() = glm::identity<glm::mat4>();
	catBlinnObject->transform.GetTransform() = glm::translate(catBlinnObject->transform.GetTransform(), { 0.0f, 0.0f, 0.0f });
	catBlinnObject->GetComponent<SpinObject>().Start();
	m_gameObjectsList.push_back(catBlinnObject);

	catMesh.meshName = "Cat Diffuse Outline";
	catDiffuseObject->tag = "CatDiffuseObject";
	catDiffuseObject->AddComponent<Miasma::RTTI::MeshRenderable>(catDiffuseObject.get(), &catMesh, textureOutline);
	catDiffuseObject->transform.GetTransform() = glm::mat4(1.0f);
	catDiffuseObject->transform.GetTransform() = glm::translate(catDiffuseObject->transform.GetTransform(), { 10.0f, 0.0f, -5.0f });
	catDiffuseObject->transform.SetPosition({ 10.0f, 0.0f, -5.0f });
	m_gameObjectsList.push_back(catDiffuseObject);

	lightObject1->tag = "RedLightObject";
	lightObject1->AddComponent<Miasma::RTTI::MeshRenderable>(lightObject1.get(), &lightTextureCreateInfo, redbasicTextureMaterial);
	lightObject1->transform.GetTransform() = glm::mat4(1.0f);
	lightObject1->transform.GetTransform() = glm::translate(lightObject1->transform.GetTransform(), { lightCreation.pos });
	m_gameObjectsList.push_back(lightObject1);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	lightObject2->tag = "GreenLightObject";
	lightObject2->AddComponent<Miasma::RTTI::MeshRenderable>(lightObject2.get(), &lightTextureCreateInfo, greenbasicTextureMaterial);
	lightObject2->transform.GetTransform() = glm::mat4(1.0f);
	lightObject2->transform.GetTransform() = glm::translate(lightObject2->transform.GetTransform(), { lightCreation2.pos });
	m_gameObjectsList.push_back(lightObject2);

	cottageObject->tag = "CottageObject"; 
	cottageObject->AddComponent<Miasma::RTTI::MeshRenderable>(cottageObject.get(), &cottageMeshCreateInfo, textureBlinnCottageMaterial);
	cottageObject->transform.GetTransform() = glm::mat4(1.0f);
	cottageObject->transform.GetTransform() = glm::translate(cottageObject->transform.GetTransform(), { 2.0f, 0.0f, -14.0f });
	m_gameObjectsList.push_back(cottageObject);

	crateObject->tag = "CrateObject";
	crateObject->AddComponent<Miasma::RTTI::MeshRenderable>(crateObject.get(), &crateMeshInfo, crateMaterial);
	crateObject->transform.GetTransform() = glm::identity<glm::mat4>();
	crateObject->transform.GetTransform() = glm::translate(crateObject->transform.GetTransform(), {4.0f, 1.0f, -7.0f});
	m_gameObjectsList.push_back(crateObject);

	quadObject->tag = "QuadObject";
	quadObject->AddComponent<Miasma::RTTI::Sprite2D>(quadObject.get(), spriteMaterial);
	quadObject->transform.GetTransform() = glm::identity<glm::mat4>();
	quadObject->transform.GetTransform() = glm::translate(quadObject->transform.GetTransform(), {700.0f, 200.0f, 1.0f });
	//quadObject->transform.GetTransform() = glm::scale(quadObject->transform.GetTransform(), { 128.0f, 64.0f, 1.0f });
	quadObject->GetComponent<Miasma::RTTI::Sprite2D>().SetSpriteSize({ 128.0f, 64.0f });
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