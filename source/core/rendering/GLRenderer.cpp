#include "rendering\GLRenderer.h"
#include "core\glad\glad.h"
#include "GLFW/glfw3.h"
#include "rendering/MeshRenderable.h"
#include "camera/Camera.h"
#include "model/Scene.h"
using namespace tdogl;

void GLRenderer::Initialize(std::shared_ptr<tdogl::Camera> camera)
{
	m_camera = camera;
}

void GLRenderer::DrawScene(std::unique_ptr<Scene>& scene)
{
	// set up framebuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// clear buffer and depth buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// loop through and render all of our meshes
	for (std::shared_ptr<MeshRenderable>& mesh : scene->GetMeshList()) {

		// use the current shader of the object
		glUseProgram(mesh->GetMaterial().GetShader());
		// setup texture 
		glUniform1i(glGetUniformLocation(mesh->GetMaterial().GetShader(), "textureSample"), 0);
		// update camera transform 
		glUniformMatrix4fv(glGetUniformLocation(mesh->GetMaterial().GetShader(), "camera"), 1, false, glm::value_ptr(m_camera->matrix()));
		
		// update transform
		glUniformMatrix4fv(glGetUniformLocation(mesh->GetMaterial().GetShader(), "model"), 1, false, glm::value_ptr(mesh->GetTransform()));
		glBindTextureUnit(0, mesh->GetMaterial().GetTextureId());
		glBindVertexArray(mesh->GetVertexArrayObject());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh->GetVertexCount());
	}
}

void GLRenderer::Shutdown()
{

}

void GLRenderer::AddMeshRenderable(std::shared_ptr<MeshRenderable> newMesh)
{
	if (newMesh) {
		m_meshList.push_back(newMesh);
	}
}