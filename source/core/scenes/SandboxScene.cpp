#include "SandboxScene.h"
#include "app/GLWindow.h"
#include "MeshRenderable.h"
#include "SpinObject.h"
#include "Sprite2D.h"
#include "Text.h"
#include "rendering/Texture2D.h"
#include "objects/GameObject.h"
#include "glm/gtc/type_ptr.hpp"
#include "utility/MeshLoader.h"
#include "gui/GUIBuilder.h"
#include "Quad.h"
#include "CollisionBody.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "FPSCameraMovement.h"
#include "FollowTransform.h"
#include "MoveObjectKeyboard.h"
using namespace Miasma::Component;
 
SandboxScene::SandboxScene(SceneCreationInfo* creationInfo) :
	IScene(creationInfo)
{
	
}

SandboxScene::~SandboxScene()
{

}

void SandboxScene::EnterScene()
{
	// enters the scene and initializes the camera 
	IScene::EnterScene();

	//m_camera->AddComponent<RigidBody>(m_camera.get());
	//m_camera->AddComponent<CapsuleCollider>(m_camera.get(), 1.0f, 3.0f);
	//m_camera->AddComponent<FPSCameraMovement>(m_camera.get(), m_glfwWindow);
	m_camera->GetComponent<Camera>().setPosition(glm::vec3(0.0f, 25.0f, 40.0f));


	// Create using a MeshRenderable
	Material textureBlinnMaterial;
	textureBlinnMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("white"));
	textureBlinnMaterial.AttachShader(m_shaderManager.GetShaderFromMap("BlinnPhong"));
	// outline
	Material textureOutline;
	textureOutline.AddTexture(TextureManager::GetInstance().GetTextureInfo("cat"));
	textureOutline.AttachShader(m_shaderManager.GetShaderFromMap("ToonShader"));
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
	// toon shader
	Material textureToonShader;
	textureToonShader.AddTexture(TextureManager::GetInstance().GetTextureInfo("cat"));
	textureToonShader.AttachShader(m_shaderManager.GetShaderFromMap("ToonShader"));
	// crate texture 
	Material crateMaterial;
	crateMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("crate1"));
	crateMaterial.AttachShader(m_shaderManager.GetShaderFromMap("ToonShader"));
	// create UI material
	Material spriteReticle;
	spriteReticle.AddTexture(TextureManager::GetInstance().GetTextureInfo("reticle"));
	spriteReticle.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));
	Material textureDefault;
	textureDefault.AddTexture(TextureManager::GetInstance().GetTextureInfo("missing"));
	textureDefault.AttachShader(m_shaderManager.GetShaderFromMap("BasicSprite"));
	// 3d sprite material
	Material sprite3dQuad;
	sprite3dQuad.AddTexture(TextureManager::GetInstance().GetTextureInfo("enemy"));
	sprite3dQuad.AttachShader(m_shaderManager.GetShaderFromMap("Billboard"));
	// ufo material
	Material ufoMaterial;
	ufoMaterial.AddTexture(TextureManager::GetInstance().GetTextureInfo("ufo"));
	ufoMaterial.AttachShader(m_shaderManager.GetShaderFromMap("ToonShader"));

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
	// ufo mesh
	MeshRenderableCreateInfo ufoMeshCreateInfo;
	ufoMeshCreateInfo.filename = "ufo.obj";
	ufoMeshCreateInfo.meshName = "UFO";
	ufoMeshCreateInfo.preTransform = glm::identity<glm::mat4>();

	// make 4 GameObjects
	std::shared_ptr<GameObject> catBlinnObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> catDiffuseObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> cottageObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> floorObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> crateObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> crateObject2 = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> quadObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> quad3dObject = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> testText = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> ufoObject = std::make_shared<GameObject>();


	// Setup MeshRenderable objects to be rendered
	catBlinnObject->tag = "CatToonObject";
	catBlinnObject->AddComponent<Miasma::Component::MeshRenderable>(catBlinnObject.get(), &catMesh, textureToonShader);
	catBlinnObject->AddComponent<Miasma::Component::SpinObject>(catBlinnObject.get(), 12.0f);
	//catBlinnObject->GetComponent<SpinObject>().Start();
	catBlinnObject->transform.translate({ 0.0f, 1.0f, 0.0f });
	m_gameObjectsList.push_back(catBlinnObject);

	catMesh.meshName = "Cat Diffuse Outline";
	catDiffuseObject->tag = "CatDiffuseObject";
	catDiffuseObject->AddComponent<Miasma::Component::MeshRenderable>(catDiffuseObject.get(), &catMesh, textureOutline);
	catDiffuseObject->transform.translate({ 6.0f, 1.0f, -5.0f });
	m_gameObjectsList.push_back(catDiffuseObject);

	lightObject1->tag = "WhiteLightObject";
	lightObject1->AddComponent<Miasma::Component::MeshRenderable>(lightObject1.get(), &lightTextureCreateInfo, redbasicTextureMaterial);
	lightObject1->transform.translate({ lightCreation.pos });
	m_gameObjectsList.push_back(lightObject1);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	lightObject2->tag = "BlueLightObject";
	lightObject2->AddComponent<Miasma::Component::MeshRenderable>(lightObject2.get(), &lightTextureCreateInfo, greenbasicTextureMaterial);
	lightObject2->transform.translate({ lightCreation2.pos });
	m_gameObjectsList.push_back(lightObject2);

	ufoObject->tag = "UFO";
	ufoObject->AddComponent<Miasma::Component::MeshRenderable>(ufoObject.get(), &ufoMeshCreateInfo, ufoMaterial);
	ufoObject->transform.translate({0.0f, 5.0f, 10.0f});
	ufoObject->AddComponent<MoveObjectKeyboard>(ufoObject.get(), m_glfwWindow, 30.0f);
	m_gameObjectsList.push_back(ufoObject);


	/*cottageObject->tag = "CottageObject"; 
	cottageObject->AddComponent<Miasma::Component::MeshRenderable>(cottageObject.get(), &cottageMeshCreateInfo, textureBlinnCottageMaterial);
	cottageObject->transform.translate({ 2.0f, 0.0f, -14.0f });
	m_gameObjectsList.push_back(cottageObject);*/

	floorObject->tag = "FloorObject";
	floorObject->AddComponent<Miasma::Component::MeshRenderable>(floorObject.get(), &floorMeshCreateInfo, greybasicTextureMaterial);
	floorObject->transform.translate({ 0.0f, 0.0f, 0.0f });
	floorObject->AddComponent<RigidBody>(floorObject.get(), rp3d::BodyType::STATIC);
	floorObject->AddComponent<BoxCollider>(floorObject.get(), glm::vec3(40.0f, 1.0f, 40.0f));
	m_gameObjectsList.push_back(floorObject);

	crateObject->tag = "CrateObject";
	crateObject->AddComponent<Miasma::Component::MeshRenderable>(crateObject.get(), &crateMeshInfo, crateMaterial);
	crateObject->transform.translate({4.0f, 10.0f, -7.0f});
	crateObject->AddComponent<RigidBody>(crateObject.get());
	crateObject->AddComponent<BoxCollider>(crateObject.get(), glm::vec3(1.0f, 1.0f, 1.0f));
	crateObject->GetComponent<RigidBody>().GetRigidBody()->setMass(rp3d::decimal(200.0));
	m_gameObjectsList.push_back(crateObject);

	crateObject2->tag = "crateObject2";
	crateObject2->AddComponent<Miasma::Component::MeshRenderable>(crateObject2.get(), &crateMeshInfo, crateMaterial);
	crateObject2->transform.translate({ -5.0f, 30.0f, -5.0f });
	crateObject2->AddComponent<RigidBody>(crateObject2.get());
	crateObject2->GetComponent<RigidBody>().GetRigidBody()->setMass(rp3d::decimal(200.0));
	crateObject2->AddComponent<BoxCollider>(crateObject2.get(), glm::vec3(1.0f, 1.0f, 1.0f));
	m_gameObjectsList.push_back(crateObject2);

	quadObject->tag = "Reticle";
	quadObject->transform.translate({960.0f, 540.0f, 1.0f });
	quadObject->AddComponent<Miasma::Component::Sprite2D>(quadObject.get(), spriteReticle);
	m_gameObjectsList.push_back(quadObject);

	quad3dObject->tag = "3DQuad";
	quad3dObject->AddComponent<Miasma::Component::MeshRenderable>(quad3dObject.get(), Quad::vertices, Quad::indices, &quadMeshInfo, sprite3dQuad);
	quad3dObject->transform.translate({5.0f, 15.0f, 5.0f});
	quad3dObject->transform.scale({1.64f, 2.28f, 1.f});
	m_gameObjectsList.push_back(quad3dObject);

	testText->tag = "TextObject";
	testText->transform.translate(glm::vec3(500.0f, 600.0f, -2.0f));
	testText->AddComponent<Text>(testText.get(), "Hello World!", glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameObjectsList.push_back(testText);

	// add a texture to the screen
	std::shared_ptr<GameObject> textureObject = std::make_shared<GameObject>();
	textureObject->tag = "TextureObject";
	textureObject->transform.translate({ 100.0f, 192.0f, 1.0f });
	textureObject->AddComponent<Sprite2D>(textureObject.get(), textureDefault);
	m_gameObjectsList.push_back(textureObject);

	//m_camera->AddComponent<FollowTransform>(m_camera.get(), ufoObject.get());

}

void SandboxScene::Update(float dt)
{
	// updates the gameobjects components
	IScene::Update(dt);
}

void SandboxScene::ExitScene()
{
	// exits the scene by clearing the gameobjects, lights, and resets the camera
	IScene::ExitScene();
}