#include "rendering\GLRenderer.h"
#include "core\glad\glad.h"
#include "GLFW/glfw3.h"
#include "rendering/MeshRenderable.h"
#include "camera/Camera.h"
#include "model/Scene.h"
using namespace tdogl;
#include "gui\GUIBuilder.h"

void GLRenderer::Initialize(GLFWwindow* pWindow, std::shared_ptr<tdogl::Camera> camera)
{
	m_camera = camera;
	// set up framebuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GUIBuilder::gbInitializeGUI(pWindow);
	glfwSetFramebufferSizeCallback(pWindow, GLRenderer::framebuffer_size_callback);
}

void GLRenderer::DrawScene(std::unique_ptr<Scene>& scene)
{
	// clear buffer and depth buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GUIBuilder::gbFeedInput();
	//GUIBuilder::gbShowImGuiDemoWindow();

	// loop through and render all of our meshes
	for (std::shared_ptr<MeshRenderable>& mesh : scene->GetMeshList()) {

		// use the current shader of the object
		glUseProgram(mesh->GetMaterial().GetShader().shaderId);
		/*
			LIGHTS
		*/
		// grab light information from shader
		glUniform3fv(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "light.color"), 1, glm::value_ptr(scene->GetLights()[0]->GetLightColor()));
		// grab light information from shader
		glUniform3fv(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "light.position"), 1, glm::value_ptr(scene->GetLights()[0]->GetLightPosition()));
		// grab light information from shader
		glUniform1f(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "light.strength"), scene->GetLights()[0]->GetLightStrength());
		// CAMERA POS 
		glUniform3fv(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "cameraPosition"), 1, glm::value_ptr(m_camera->position()));
		
		// setup texture (get texture location "textureSample")
		glUniform1i(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "textureSample"), 0);
		// update camera transform 
		glUniformMatrix4fv(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "camera"), 1, false, glm::value_ptr(m_camera->matrix()));
		
		// update transform
		glUniformMatrix4fv(glGetUniformLocation(mesh->GetMaterial().GetShader().shaderId, "model"), 1, false, glm::value_ptr(mesh->GetTransform()));
		glBindTextureUnit(0, mesh->GetMaterial().GetTextureId());
		glBindVertexArray(mesh->GetVertexArrayObject());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh->GetVertexCount());
	}
	GUIBuilder::gbSceneInfoOverlay(m_camera);
	GUIBuilder::gbSceneObjectsInfo(scene);
	GUIBuilder::gbRenderGUI();
}

void GLRenderer::Shutdown()
{
	GUIBuilder::gbShutdownGUI();
}

void GLRenderer::AddMeshRenderable(std::shared_ptr<MeshRenderable> newMesh)
{
	if (newMesh) {
		m_meshList.push_back(newMesh);
	}
}

void GLRenderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}