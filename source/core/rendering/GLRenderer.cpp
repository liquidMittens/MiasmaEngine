#include "rendering/GLRenderer.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "components/MeshRenderable.h"
#include "camera/Camera.h"
#include "model/Scene.h"
#include "app/GLWindow.h"
#include "gui/GUIBuilder.h"
#include <iostream>
#include <sstream>
#include "objects/GameObject.h"
using namespace tdogl;
using namespace Miasma::Renderer;
using namespace Miasma::RTTI;
using namespace Miasma::UI;

void GLRenderer::Initialize(GLWindow* pWindow, std::shared_ptr<tdogl::Camera> camera)
{
	m_camera = camera;
	if (!m_camera) {
		std::cout << "ERROR: GLRenderer Camera is NULL\n";
	}
	// set up framebuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Miasma::UI::GUIBuilder::gbInitializeGUI(pWindow->GetGLFWWindow());
	glfwSetFramebufferSizeCallback(pWindow->GetGLFWWindow(), GLRenderer::framebuffer_size_callback);
}

bool GLRenderer::DrawScene(std::unique_ptr<Scene>& scene)
{
	bool drewFrame = true;
	if (m_camera && scene) {
		// clear buffer and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Miasma::UI::GUIBuilder::gbFeedInput();
		//GUIBuilder::gbShowImGuiDemoWindow();

		int lightIndex = 0;
		// loop through and render all of our meshes
		for (auto& gameObject : scene->GetGameObjectsList()) {
			Miasma::RTTI::MeshRenderable& mesh = gameObject->GetComponent<Miasma::RTTI::MeshRenderable>();
			if (&mesh == nullptr) {
				continue;
			}
			// use the current shader of the object
			glUseProgram(mesh.GetMaterial().GetShader().shaderId);
			/*
				LIGHTS
			*/
			std::stringstream lightIndexed;
			for (int lightIndex = 0; lightIndex < scene->GetLights().size(); ++lightIndex) {
				Miasma::RTTI::PointLight& light = scene->GetLights()[lightIndex]->GetComponent<PointLight>();
				// grab light information from shader (color)
				lightIndexed.str("");
				lightIndexed << "light[" << lightIndex << "]";
				glUniform3fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, lightIndexed.str().append(".color").c_str()), 1, glm::value_ptr(light.GetLightColor()));
				// grab light information from shader (pos)
				lightIndexed.str("");
				lightIndexed << "light[" << lightIndex << "]";
				glUniform3fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, lightIndexed.str().append(".position").c_str()), 1, glm::value_ptr(light.GetLightPosition()));
				// grab light information from shader (strength)
				lightIndexed.str("");
				lightIndexed << "light[" << lightIndex << "]";
				glUniform1f(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, lightIndexed.str().append(".strength").c_str()), light.GetLightStrength());
			}
			// TEST: passing outline light
			// grab light information from shader (color)
			glUniform3fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "light.color"), 1, glm::value_ptr(scene->GetLights()[0]->GetComponent<PointLight>().GetLightColor()));
			// grab light information from shader (pos)
			glUniform3fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "light.position"), 1, glm::value_ptr(scene->GetLights()[0]->GetComponent<PointLight>().GetLightColor()));
			// grab light information from shader (strength)
			glUniform1f(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "light.strength"), scene->GetLights()[0]->GetComponent<PointLight>().GetLightStrength());

			// CAMERA POS 
			glUniform3fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "cameraPosition"), 1, glm::value_ptr(m_camera->position()));
			// setup texture (get texture location "textureSample")
			glUniform1i(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "textureSample"), 0);
			// update camera transform 
			glUniformMatrix4fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "camera"), 1, false, glm::value_ptr(m_camera->matrix()));

			// update transform
			glUniformMatrix4fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "model"), 1, false, glm::value_ptr(gameObject->transform.GetTransform()));
			glBindTextureUnit(0, mesh.GetMaterial().GetTextureId());
			glBindVertexArray(mesh.GetVertexArrayObject());
			glBindBuffer(GL_ARRAY_BUFFER, mesh.GetVertexBufferObject());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBufferObject());
			// stencil info
			// stencil buffer is updated with 1s where the containers were drawn 
			//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			//glStencilFunc(GL_ALWAYS, 1, 0xff);
			//glStencilMask(0xff);
			if (mesh.GetMeshDrawType() == EMeshDrawType::EMESH_TYPE_TRIANGLES) {
				glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);
			}
			else if (mesh.GetMeshDrawType() == EMeshDrawType::EMESH_TYPE_TRIANGLEARRAY) {
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.GetVertexCount());
			}
			// draw the upscaled containers but this time with the appropriate test function and disabling writes to the stencil buffer: 
			//glStencilFunc(GL_NOTEQUAL, 1, 0xff);
			//glStencilMask(0x00);
			//glDisable(GL_DEPTH_TEST);
			//glDrawElements(GL_TRIANGLES, (GLsizei)mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0);
		}
		Miasma::UI::GUIBuilder::gbSceneInfoOverlay(m_camera);
		Miasma::UI::GUIBuilder::gbSceneObjectsInfo(scene);
		Miasma::UI::GUIBuilder::gbRenderGUI();
	}
	else {
		if (!scene) {
			std::cout << "ERROR: GLRenderer scene is NULL\n";
			drewFrame = false;
		}
	}
	return drewFrame;
}

void GLRenderer::Shutdown()
{
	Miasma::UI::GUIBuilder::gbShutdownGUI();
}

void GLRenderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}