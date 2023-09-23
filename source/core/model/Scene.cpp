#include "model/Scene.h"
#include "objects/MeshRenderable.h"
#include "model/Cube.h"
#include "model/Rectangle.h"
#include "app/GLWindow.h"
#include "rendering/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "utility/MeshLoader.h"
#include "gui/GUIBuilder.h"
 
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
	MeshRenderableCreateInfo catMesh;
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

	// Setup MeshRenderable objects to be rendered
	std::shared_ptr<MeshRenderable> catMeshBlinn(new MeshRenderable(&catMesh, textureBlinnMaterial));
	catMeshBlinn->GetTransform() = glm::mat4(1.0f);
	catMeshBlinn->GetTransform() = glm::translate(catMeshBlinn->GetTransform(), { 0.0f, 0.0f, 0.0f });
	catMeshBlinn->GetTransform() = glm::rotate(catMeshBlinn->GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	m_meshRenderableList.push_back(catMeshBlinn);

	catMesh.meshName = "Cat Diffuse Outline";
	std::shared_ptr<MeshRenderable> catMeshDiffuse(new MeshRenderable(&catMesh, textureOutline));
	catMeshDiffuse->GetTransform() = glm::mat4(1.0f);
	catMeshDiffuse->GetTransform() = glm::translate(catMeshDiffuse->GetTransform(), { 10.0f, 0.0f, -5.0f });
	catMeshDiffuse->GetTransform() = glm::rotate(catMeshDiffuse->GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	m_meshRenderableList.push_back(catMeshDiffuse);

	std::shared_ptr<MeshRenderable> lightMesh(new MeshRenderable(&lightTextureCreateInfo, redbasicTextureMaterial));
	lightMesh->GetTransform() = glm::mat4(1.0f);
	lightMesh->GetTransform() = glm::translate(lightMesh->GetTransform(), { lightCreation.pos });
	m_meshRenderableList.push_back(lightMesh);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	std::shared_ptr<MeshRenderable> lightMesh2(new MeshRenderable(&lightTextureCreateInfo, greenbasicTextureMaterial));
	lightMesh2->GetTransform() = glm::mat4(1.0f);
	lightMesh2->GetTransform() = glm::translate(lightMesh2->GetTransform(), { lightCreation2.pos });
	m_meshRenderableList.push_back(lightMesh2);

	std::shared_ptr<MeshRenderable> cottageMesh(new MeshRenderable(&cottageMeshCreateInfo, textureBlinnCottageMaterial));
	cottageMesh->GetTransform() = glm::mat4(1.0f);
	cottageMesh->GetTransform() = glm::translate(cottageMesh->GetTransform(), { 2.0f, 0.0f, -14.0f });
	m_meshRenderableList.push_back(cottageMesh);
}

void Scene::Update(float dt)
{
	float angle = glm::radians<float>(10.0f * (float)glfwGetTime());

}

void Scene::ExitScene()
{

}