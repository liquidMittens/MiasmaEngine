#ifndef SCENE_H_
#define SCENE_H_

#include <memory>
#include "camera/Camera.h"
#include <vector>
#include "GLFW/glfw3.h"
#include "managers/ShaderManager.h"
#include "managers/TextureManager.h"
#include "model/Light.h"

class MeshRenderable;
class GLWindow;
using MeshRenderableListType = std::vector<std::shared_ptr<MeshRenderable>>;
using LightListType = std::vector<std::unique_ptr<Light>>;

constexpr float FOV = 45.0f;
constexpr float moveSpeed = 5.0; //units per second
constexpr float zoomSensitivity = -0.5f;


struct SceneCreationInfo
{
	GLWindow* pWindow;
	glm::vec2 screenSize;
};

class Scene
{
	friend class GUIBuilder;

public:
	Scene(SceneCreationInfo* creationInfo);
	~Scene();
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	void EnterScene();
	void Update(float dt);
	void ExitScene();

	std::shared_ptr<tdogl::Camera> GetCamera() { return m_camera; }
	MeshRenderableListType GetMeshList() { return m_meshRenderableList; }
	LightListType& GetLights() { return m_lights; }
	GLFWwindow* GetGLFWWindow() { return m_glfwWindow; }

private:
	std::shared_ptr<tdogl::Camera> m_camera;
	MeshRenderableListType m_meshRenderableList;
	GLFWwindow* m_glfwWindow;
	glm::vec2 m_screenSize;
	// calculate delta time per frame
	float currTime;
	float m_deltaTime;
	ShaderManager m_shaderManager;
	TextureManager m_textureManager;
	// fps info
	double m_lastTime;
	double m_currentTime;
	int m_numFrames;
	float m_frameTime;
	LightListType m_lights;
};

#endif
