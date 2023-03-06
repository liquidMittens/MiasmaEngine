#include "model\Scene.h"
#include "rendering/MeshRenderable.h"
#include "objects/Cube.h"
#include "objects/Rectangle.h"
#include "rendering/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

double Scene::m_scrollY = 0.0;
 
Scene::Scene(SceneCreationInfo* creationInfo)
{
	m_glfwWindow = creationInfo->pWindow;
	m_screenSize.x = creationInfo->screenSize.x;
	m_screenSize.y = creationInfo->screenSize.y;
	// register callbacks 
	glfwSetScrollCallback(m_glfwWindow, Scene::OnScroll);
	m_camera = std::make_shared<tdogl::Camera>();
	m_camera->initcamera(45.0f, 0.1f, 100.0f, glm::vec3(0, 0, 4), glm::vec2(m_screenSize.x, m_screenSize.y));
}

Scene::~Scene()
{

}

void Scene::EnterScene()
{
	m_camera->initcamera(45.0f, 0.1f, 100.0f, glm::vec3(0, 0, 4), glm::vec2(m_screenSize.x, m_screenSize.y));
	// create a cube mesh renderable
	m_shaderManager.LoadShader("BasicColor", ShaderType::BasicColor);
	std::cout << "Got Shader #: " << m_shaderManager.GetShaderFromMap(ShaderType::BasicColor) << '\n';
	m_shaderManager.LoadShader("BasicTexture", ShaderType::BasicTexture);
	std::cout << "Got Shader #: " << m_shaderManager.GetShaderFromMap(ShaderType::BasicTexture) << '\n';
	m_shaderManager.LoadShader("BasicColorTexture", ShaderType::BasicColorTexture);
	std::cout << "Got Shader #: " << m_shaderManager.GetShaderFromMap(ShaderType::BasicColorTexture) << '\n';
	std::cout << "Got Bad Shader #: " << m_shaderManager.GetShaderFromMap(ShaderType::Unknown) << '\n';
	m_textureManager.LoadTexture("stone");
	m_textureManager.LoadTexture("banana");

	// Create using a MeshRenderable
	Material textureColorMaterial;
	textureColorMaterial.AddTexture(m_textureManager.GetTextureInfo("stone")->GetTextureName(), m_textureManager.GetTextureInfo("stone")->GetTextureId());
	textureColorMaterial.AttachShader(ShaderType::BasicTexture, m_shaderManager.GetShaderFromMap(ShaderType::BasicTexture));
	Material textureColorMaterial2;
	textureColorMaterial2.AddTexture(m_textureManager.GetTextureInfo("banana")->GetTextureName(), m_textureManager.GetTextureInfo("banana")->GetTextureId());
	textureColorMaterial2.AttachShader(ShaderType::BasicColor, m_shaderManager.GetShaderFromMap(ShaderType::BasicColor));
	std::shared_ptr<MeshRenderable> cubeMesh(new MeshRenderable(Cube::vertices, textureColorMaterial));
	m_meshRenderableList.push_back(cubeMesh);

	Rectangle::Rectangle rect(2.0f, 1.0f, 5.0f);
	std::shared_ptr<MeshRenderable> cubeMesh2(new MeshRenderable(rect.vertices, textureColorMaterial2));
	m_meshRenderableList.push_back(cubeMesh2);
}

void Scene::Update(float dt)
{
	ProcessInput(m_glfwWindow, dt);
	float angle = glm::radians<float>(10.0f * (float)glfwGetTime());
	auto cubeMesh = m_meshRenderableList.at(0);
	cubeMesh->GetTransform() = glm::mat4(1.0f);
	cubeMesh->GetTransform() = glm::translate(cubeMesh->GetTransform(), {0.0f, 0.0f, -5.0f});
	cubeMesh->GetTransform() = glm::rotate(cubeMesh->GetTransform(), 2.0f * angle, { 0.0f, 1.0f, 0.0f });
	cubeMesh->GetTransform() = glm::rotate(cubeMesh->GetTransform(), 5.0f * angle, { 1.0f, 1.0f, 0.0f });

	auto cubeMesh2 = m_meshRenderableList.at(1);
	cubeMesh2->GetTransform() = glm::mat4(1.0f);
	cubeMesh2->GetTransform() = glm::translate(cubeMesh2->GetTransform(), { 5.0f, 0.0f, -10.0f });
	//cubeMesh2->GetTransform() = glm::rotate(cubeMesh2->GetTransform(), 1.0f * angle, { 0.0f, 1.0f, 0.0f });
	//cubeMesh2->GetTransform() = glm::rotate(cubeMesh2->GetTransform(), 1.0f * angle, { 1.0f, 1.0f, 0.0f });
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

		char buffer[1024];
		memset(buffer, '\0', 1024);

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

// records how far the y axis has been scrolled
void Scene::OnScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	m_scrollY += deltaY;
}