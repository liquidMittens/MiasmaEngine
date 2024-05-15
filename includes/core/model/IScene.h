#ifndef ISCENE_H_
#define ISCENE_H_

#include <memory>
#include "camera/Camera.h"
#include <vector>
#include "managers/ShaderManager.h"
#include "managers/TextureManager.h"
#include "GLFW/glfw3.h"
#include "GUIBuilder.h"

class GLWindow;
using LightListType = std::vector<std::shared_ptr<GameObject>>;
using GameObjectsList = std::vector<std::shared_ptr<GameObject>>;

constexpr float FOV = 45.0f;
constexpr float moveSpeed = 2500.0;
constexpr float jumpForce = 100000.0;
constexpr float zoomSensitivity = -0.5f;


struct SceneCreationInfo
{
	GLWindow* pWindow;
	glm::vec2 screenSize;
	bool scene2dRenderer;
};

class IScene
{
	friend class Miasma::UI::GUIBuilder;

public: 

	IScene(SceneCreationInfo* creationInfo);
	~IScene();
	IScene(const IScene&) = delete;
	IScene& operator=(const IScene&) = delete;

	virtual void EnterScene();
	virtual void Update(float dt);
	virtual void ExitScene();

	std::shared_ptr<GameObject> GetCamera() { return m_camera; }
	GameObjectsList GetGameObjectsList() { return m_gameObjectsList; }
	LightListType GetLights() { return m_lights; }
	GLFWwindow* GetGLFWWindow() { return m_glfwWindow; }

protected:
	std::shared_ptr<GameObject> m_camera;
	GameObjectsList m_gameObjectsList;
	LightListType m_lights;
	ShaderManager m_shaderManager;
	GLFWwindow* m_glfwWindow;
	glm::vec2 m_screenSize;
	bool m_2dRenderer;
};

#endif
