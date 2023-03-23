#include "model/Scene.h"
#include "rendering/MeshRenderable.h"
#include "model/Cube.h"
#include "model/Rectangle.h"
#include "rendering/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "utility/MeshLoader.h"

double Scene::m_scrollY = 0.0;
bool Scene::m_mouseModeEnabled = false;
 
Scene::Scene(SceneCreationInfo* creationInfo)
{
	m_glfwWindow = creationInfo->pWindow;
	m_screenSize.x = creationInfo->screenSize.x;
	m_screenSize.y = creationInfo->screenSize.y;
	// register callbacks 
	glfwSetScrollCallback(m_glfwWindow, Scene::OnScroll);
	glfwSetMouseButtonCallback(m_glfwWindow, Scene::OnMouseButton);
	m_camera = std::make_shared<tdogl::Camera>();
	m_camera->initcamera(90.0f, 0.1f, 100.0f, glm::vec3(0, 0, 14), glm::vec2(m_screenSize.x, m_screenSize.y));
	m_mouseModeEnabled = false;
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

	std::shared_ptr<MeshRenderable> catMeshBlinn(new MeshRenderable(&catMesh, textureBlinnMaterial));
	m_meshRenderableList.push_back(catMeshBlinn);

	catMesh.meshName = "Cat Diffuse Outline";
	std::shared_ptr<MeshRenderable> catMeshDiffuse(new MeshRenderable(&catMesh, textureOutline));
	m_meshRenderableList.push_back(catMeshDiffuse);

	std::shared_ptr<MeshRenderable> lightMesh(new MeshRenderable(&lightTextureCreateInfo, redbasicTextureMaterial));
	m_meshRenderableList.push_back(lightMesh);

	lightTextureCreateInfo.meshName = "Left Light Mesh";
	std::shared_ptr<MeshRenderable> lightMesh2(new MeshRenderable(&lightTextureCreateInfo, greenbasicTextureMaterial));
	m_meshRenderableList.push_back(lightMesh2);

	std::shared_ptr<MeshRenderable> cottageMesh(new MeshRenderable(&cottageMeshCreateInfo, textureBlinnCottageMaterial));
	m_meshRenderableList.push_back(cottageMesh);

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
}

void Scene::Update(float dt)
{
	ProcessInput(m_glfwWindow, dt);
	float angle = glm::radians<float>(10.0f * (float)glfwGetTime());
	auto cubeMesh = m_meshRenderableList.at(0);
	cubeMesh->GetTransform() = glm::mat4(1.0f);
	cubeMesh->GetTransform() = glm::translate(cubeMesh->GetTransform(), {0.0f, 0.0f, 0.0f});
	cubeMesh->GetTransform() = glm::rotate(cubeMesh->GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	cubeMesh->GetTransform() = glm::rotate(cubeMesh->GetTransform(), 2.0f * angle, { 0.0f, 0.0f, 1.0f });
	//cubeMesh->GetTransform() = glm::rotate(cubeMesh->GetTransform(), 5.0f * angle, { 1.0f, 1.0f, 0.0f });

	auto cubeMesh2 = m_meshRenderableList.at(1);
	cubeMesh2->GetTransform() = glm::mat4(1.0f);
	cubeMesh2->GetTransform() = glm::translate(cubeMesh2->GetTransform(), { 10.0f, 0.0f, -5.0f });
	cubeMesh2->GetTransform() = glm::rotate(cubeMesh2->GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
	//cubeMesh2->GetTransform() = glm::rotate(cubeMesh2->GetTransform(), 1.0f * angle, { 1.0f, 1.0f, 0.0f });

	auto lightMesh = m_meshRenderableList.at(2);
	lightMesh->GetTransform() = glm::mat4(1.0f);
	lightMesh->GetTransform() = glm::translate(lightMesh->GetTransform(), { m_lights[0]->GetLightPosition() });

	auto lightMesh2 = m_meshRenderableList.at(3);
	lightMesh2->GetTransform() = glm::mat4(1.0f);
	lightMesh2->GetTransform() = glm::translate(lightMesh2->GetTransform(), { m_lights[1]->GetLightPosition() });
	//lightMesh2->GetTransform() = glm::scale(lightMesh2->GetTransform(), glm::vec3(1.0));

	auto cottageMesh = m_meshRenderableList.at(4);
	cottageMesh->GetTransform() = glm::mat4(1.0f);
	cottageMesh->GetTransform() = glm::translate(cottageMesh->GetTransform(), { 2.0f, 0.0f, -14.0f });

}

void Scene::ExitScene()
{

}

void Scene::ProcessInput(GLFWwindow* pWindow, float deltaTime)
{
	if (pWindow != nullptr) {
		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(pWindow, true);
		}
		if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS) {
			m_wireframe = !m_wireframe;
		}
		//move position of camera based on WASD keys, and XZ keys for up and down
		if (glfwGetKey(pWindow, 'S')) {
			m_camera->offsetPosition(deltaTime * moveSpeed * -m_camera->forward());
		}
		else if (glfwGetKey(pWindow, 'W')) {
			m_camera->offsetPosition(deltaTime * moveSpeed * m_camera->forward());
		}
		if (glfwGetKey(pWindow, 'A')) {
			m_camera->offsetPosition(deltaTime * moveSpeed * -m_camera->right());
		}
		else if (glfwGetKey(pWindow, 'D')) {
			m_camera->offsetPosition(deltaTime * moveSpeed * m_camera->right());
		}
		if (glfwGetKey(pWindow, GLFW_KEY_LEFT_CONTROL)) {
			m_camera->offsetPosition(deltaTime * moveSpeed * -glm::vec3(0, 1, 0));
		}
		else if (glfwGetKey(pWindow, GLFW_KEY_SPACE)) {
			m_camera->offsetPosition(deltaTime * moveSpeed * glm::vec3(0, 1, 0));
		}

		if (!m_mouseModeEnabled) {
			//rotate camera based on mouse movement
			const float mouseSensitivity = 0.1f;
			double mouseX, mouseY;
			glfwGetCursorPos(pWindow, &mouseX, &mouseY);
			m_camera->offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
			glfwSetCursorPos(pWindow, 0, 0); //reset the mouse, so it doesn't go out of the window

			//increase or decrease field of view based on mouse wheel
			float fieldOfView = m_camera->fieldOfView() + zoomSensitivity * (float)m_scrollY;
			if (fieldOfView < 5.0f) fieldOfView = 5.0f;
			if (fieldOfView > 130.0f) fieldOfView = 130.0f;
			m_camera->setFieldOfView(fieldOfView);
			m_scrollY = 0;
		}
	}
}

// records how far the y axis has been scrolled
void Scene::OnScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	m_scrollY += deltaY;
}

void Scene::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
		std::cout << "clicked mouse button right\n";
		m_mouseModeEnabled = !m_mouseModeEnabled;
		if (m_mouseModeEnabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}