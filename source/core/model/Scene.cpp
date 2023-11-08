#include "model/Scene.h"
#include "app/GLWindow.h"
#include "MeshRenderable.h"
#include "SpinObject.h"
#include "Sprite2D.h"
#include "rendering/Texture2D.h"
#include "objects/GameObject.h"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "utility/MeshLoader.h"
#include "gui/GUIBuilder.h"
#include "model/Quad.h"
#include "CollisionBody.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
using namespace Miasma::RTTI;
 
Scene::Scene(SceneCreationInfo* creationInfo)
{
	m_glfwWindow = creationInfo->pWindow->GetGLFWWindow();
	m_screenSize.x = creationInfo->screenSize.x;
	m_screenSize.y = creationInfo->screenSize.y;
	m_camera = std::make_shared<GameObject>();
	// attach the camera component
	m_camera->AddComponent<tdogl::Camera>(m_camera.get());
	m_gameObjectsList.push_back(m_camera);
}

Scene::~Scene()
{

}

void Scene::EnterScene()
{
	m_camera->GetComponent<Camera>().initcamera(90.0f, 0.1f, 1000.0f, glm::vec3(0, 3, 14), glm::vec2(m_screenSize.x, m_screenSize.y));
	m_camera->AddComponent<RigidBody>(m_camera.get());
	m_camera->AddComponent<CapsuleCollider>(m_camera.get(), 3.0f, 5.0f);

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
	// white
	Material greybasicTextureMaterial;
	greybasicTextureMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("grey"));
	greybasicTextureMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// cottage Blinn
	Material textureBlinnCottageMaterial;
	textureBlinnCottageMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("cottage"));
	textureBlinnCottageMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// crate texture 
	Material crateMaterial;
	crateMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("crate1"));
	crateMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// create UI material
	Material spriteReticle;
	spriteReticle.AddTexture(TextureManager::GetInstance().GetTextureInfo("reticle"));
	spriteReticle.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));
	// 3d sprite material
	Material sprite3dQuad;
	sprite3dQuad.AddTexture(TextureManager::GetInstance().GetTextureInfo("enemy"));
	sprite3dQuad.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));

	// Setup lights 
	// create lights
	LightCreationInfo lightCreation;
	lightCreation.color = glm::vec3(1.0f, 1.0f, 1.0f);
	lightCreation.pos = glm::vec3(4.0f, 8.0f, 3.0f);
	lightCreation.lightStrength = 20.0f;
	std::shared_ptr<GameObject> lightObject1 = std::make_shared<GameObject>();
	lightObject1->AddComponent<PointLight>(lightObject1.get(), &lightCreation);
	m_lights.push_back(lightObject1);

	LightCreationInfo lightCreation2;
	lightCreation2.color = glm::vec3(0.8f, 0.0f, 1.0f);
	lightCreation2.pos = glm::vec3(-3.0f, 5.0f, 0.0f);
	lightCreation2.lightStrength = 30.0f;
	std::shared_ptr<GameObject> lightObject2 = std::make_shared<GameObject>();
	lightObject2->AddComponent<PointLight>(lightObject2.get(), &lightCreation2);
	m_lights.push_back(lightObject2);

	
	// load two meshes
	MeshRenderableCreateInfo catMesh;
	catMesh.filename = "catnormal.obj";
	catMesh.meshName = "cat blinn";
	catMesh.preTransform = 0.1f * glm::mat4(1.0f);
	MeshRenderableCreateInfo lightTextureCreateInfo;
	lightTextureCreateInfo.filename = "cube.obj";
	lightTextureCreateInfo.meshName = "Light Mesh";
	lightTextureCreateInfo.preTransform = 0.05f * glm::mat4(1.0f);
	MeshRenderableCreateInfo cottageMeshCreateInfo;
	cottageMeshCreateInfo.filename = "cottage.obj";
	cottageMeshCreateInfo.meshName = "Cottage Mesh";
	cottageMeshCreateInfo.preTransform = 0.5f * glm::mat4(1.0f);
	// load cube mesh
	MeshRenderableCreateInfo crateMeshInfo;
	crateMeshInfo.filename = "Crate1.obj";
	crateMeshInfo.meshName = "Crate Mesh";
	crateMeshInfo.preTransform = glm::mat4(1.0f);
	// load a quad
	MeshRenderableCreateInfo quadMeshInfo;
	quadMeshInfo.filename = "QuadTest";
	quadMeshInfo.meshName = "QuadTest";
	quadMeshInfo.preTransform = glm::identity<glm::mat4>();
	// floor mesh
	MeshRenderableCreateInfo floorMeshCreateInfo;
	floorMeshCreateInfo.filename = "floor.obj";
	floorMeshCreateInfo.meshName = "floor";
	floorMeshCreateInfo.preTransform = glm::identity<glm::mat4>();

	// make 4 GameObjects
	std::shared_ptr<GameObject> catBlinnObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> catDiffuseObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> cottageObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> floorObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> crateObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> crateObject2 = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> quadObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> quad3dObject = std::make_shared<GameObject>();


	// Setup MeshRenderable objects to be rendered
	catBlinnObject->tag = "CatBlinnObject";
	catBlinnObject->AddComponent<Miasma::RTTI::MeshRenderable>(catBlinnObject.get(), &catMesh, textureBlinnMaterial);
	catBlinnObject->AddComponent<Miasma::RTTI::SpinObject>(catBlinnObject.get(), 2.0f);
	catBlinnObject->GetComponent<SpinObject>().Start();
	catBlinnObject->transform.translate({ 0.0f, 1.0f, 0.0f });
	m_gameObjectsList.push_back(catBlinnObject);

	catMesh.meshName = "Cat Diffuse Outline";
	catDiffuseObject->tag = "CatDiffuseObject";
	catDiffuseObject->AddComponent<Miasma::RTTI::MeshRenderable>(catDiffuseObject.get(), &catMesh, textureOutline);
	catDiffuseObject->transform.translate({ 6.0f, 1.0f, -5.0f });
	m_gameObjectsList.push_back(catDiffuseObject);

	lightObject1->tag = "WhiteLightObject";
	lightObject1->AddComponent<Miasma::RTTI::MeshRenderable>(lightObject1.get(), &lightTextureCreateInfo, redbasicTextureMaterial);
	lightObject1->transform.translate({ lightCreation.pos });
	m_gameObjectsList.push_back(lightObject1);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	lightObject2->tag = "BlueLightObject";
	lightObject2->AddComponent<Miasma::RTTI::MeshRenderable>(lightObject2.get(), &lightTextureCreateInfo, greenbasicTextureMaterial);
	lightObject2->transform.translate({ lightCreation2.pos });
	m_gameObjectsList.push_back(lightObject2);

	/*cottageObject->tag = "CottageObject"; 
	cottageObject->AddComponent<Miasma::RTTI::MeshRenderable>(cottageObject.get(), &cottageMeshCreateInfo, textureBlinnCottageMaterial);
	cottageObject->transform.translate({ 2.0f, 0.0f, -14.0f });
	m_gameObjectsList.push_back(cottageObject);*/

	floorObject->tag = "FloorObject";
	floorObject->AddComponent<Miasma::RTTI::MeshRenderable>(floorObject.get(), &floorMeshCreateInfo, greybasicTextureMaterial);
	floorObject->transform.translate({ 0.0f, 0.0f, 0.0f });
	floorObject->AddComponent<RigidBody>(floorObject.get(), rp3d::BodyType::STATIC);
	//floorObject->GetComponent<RigidBody>().GetCollider()->enableGravity(false);
	//floorObject->GetComponent<RigidBody>().GetCollider()->setMass(0.0);
	floorObject->AddComponent<BoxCollider>(floorObject.get(), glm::vec3(10.0f, 0.5f, 10.0f));
	m_gameObjectsList.push_back(floorObject);

	crateObject->tag = "CrateObject";
	crateObject->AddComponent<Miasma::RTTI::MeshRenderable>(crateObject.get(), &crateMeshInfo, crateMaterial);
	crateObject->transform.translate({4.0f, 10.0f, -7.0f});
	crateObject->AddComponent<RigidBody>(crateObject.get());
	crateObject->AddComponent<BoxCollider>(crateObject.get(), glm::vec3(1.0f, 1.0f, 1.0f));
	m_gameObjectsList.push_back(crateObject);

	crateObject2->tag = "crateObject2";
	crateObject2->AddComponent<Miasma::RTTI::MeshRenderable>(crateObject2.get(), &crateMeshInfo, crateMaterial);
	crateObject2->transform.translate({ -5.0f, 30.0f, -5.0f });
	crateObject2->AddComponent<RigidBody>(crateObject2.get());
	crateObject2->AddComponent<CapsuleCollider>(crateObject2.get(), 2.0f, 1.0f);
	m_gameObjectsList.push_back(crateObject2);

	quadObject->tag = "Reticle";
	quadObject->transform.translate({960.0f, 540.0f, 1.0f });
	quadObject->AddComponent<Miasma::RTTI::Sprite2D>(quadObject.get(), spriteReticle);
	m_gameObjectsList.push_back(quadObject);

	quad3dObject->tag = "3DQuad";
	quad3dObject->AddComponent<Miasma::RTTI::MeshRenderable>(quad3dObject.get(), Quad::vertices, Quad::indices, &quadMeshInfo, sprite3dQuad);
	quad3dObject->transform.translate({5.0f, 2.0f, 5.0f});
	quad3dObject->transform.scale({1.64f, 2.28f, 1.f});
	m_gameObjectsList.push_back(quad3dObject);
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