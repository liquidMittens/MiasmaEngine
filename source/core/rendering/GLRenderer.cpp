#include "rendering/GLRenderer.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#define GLT_IMPLEMENTATION
#include "glText/gltext.h"
#include "components/MeshRenderable.h"
#include "camera/Camera.h"
#include "model/IScene.h"
#include "components/PointLight.h"
#include "app/GLWindow.h"
#include "gui/GUIBuilder.h"
#include <iostream>
#include <sstream>
#include "util.h"
using namespace tdogl;
using namespace Miasma::Renderer;
using namespace Miasma::Component;
using namespace Miasma::UI;


GLRenderer::GLRenderer()
{

}

GLRenderer::~GLRenderer()
{

}

void GLRenderer::Initialize(GLWindow* pWindow)
{
	// set up framebuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Miasma::UI::GUIBuilder::gbInitializeGUI(pWindow->GetGLFWWindow());
	glfwSetFramebufferSizeCallback(pWindow->GetGLFWWindow(), GLRenderer::framebuffer_size_callback);
	gltInit();
}

void GLRenderer::DrawTextObjects(Miasma::Component::Text* textComponent)
{
	gltBeginDraw();
	gltColor(textComponent->GetTextColor().x, textComponent->GetTextColor().y, textComponent->GetTextColor().z, 1.0f);
	gltDrawText2D(textComponent->GetGLTtext(), textComponent->gameObject->transform.GetPosition().x, textComponent->gameObject->transform.GetPosition().y, textComponent->GetTextScale());
	gltEndDraw();
}

bool GLRenderer::DrawScene(std::unique_ptr<IScene>& scene)
{
	bool drewFrame = true;
	if (scene) {
		// get the camera 
		tdogl::Camera camera = scene->GetCamera()->GetComponent<Camera>();
		// clear buffer and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Miasma::UI::GUIBuilder::gbFeedInput();
		//GUIBuilder::gbShowImGuiDemoWindow();

		int lightIndex = 0;
		// loop through and render all of our meshes
		for (auto& gameObject : scene->GetGameObjectsList()) {
			MeshRenderable& mesh = gameObject->GetComponent<MeshRenderable>();
			Sprite2D& sprite = gameObject->GetComponent<Sprite2D>();
			Miasma::Component::Text& textComponent = gameObject->GetComponent<Miasma::Component::Text>();

			if (!gameObject->IsActive()) {
				continue;
			}

			// mesh rendering
			if (&mesh != nullptr) {
				// use the current shader of the object
				glUseProgram(mesh.GetMaterial().GetShader().shaderId);
				/*
					LIGHTS
				*/
				std::stringstream lightIndexed;
				for (int lightIndex = 0; lightIndex < scene->GetLights().size(); ++lightIndex) {
					Miasma::Component::PointLight& light = scene->GetLights()[lightIndex]->GetComponent<PointLight>();
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
				glUniform3fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "cameraPosition"), 1, glm::value_ptr(camera.position()));
				// setup texture (get texture location "textureSample")
				glUniform1i(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "textureSample"), 0);
				// update camera transform 
				glUniformMatrix4fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "viewproj"), 1, false, glm::value_ptr(camera.matrix()));
				glUniformMatrix4fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "view"), 1, false, glm::value_ptr(camera.view()));
				glUniformMatrix4fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "proj"), 1, false, glm::value_ptr(camera.projection()));

				// update transform
				glUniformMatrix4fv(glGetUniformLocation(mesh.GetMaterial().GetShader().shaderId, "model"), 1, false, glm::value_ptr(gameObject->transform.GetTransform()));
				glBindTextureUnit(0, mesh.GetMaterial().GetTextureId());
				glBindVertexArray(mesh.GetVertexArrayObject());
				glBindBuffer(GL_ARRAY_BUFFER, mesh.GetVertexBufferObject());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBufferObject());

				if (mesh.GetMeshDrawType() == EMeshDrawType::EMESH_TYPE_TRIANGLES) {
					glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);
				}
				else if (mesh.GetMeshDrawType() == EMeshDrawType::EMESH_TYPE_TRIANGLEARRAY) {
					glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.GetVertexCount());
				}
			}
			// sprite rendering
			if (&sprite != nullptr) {
				RenderSprite(scene, gameObject);
			}
			// text rendering
			if (&textComponent != nullptr) {
				DrawTextObjects(&textComponent);
			}
		}
		Miasma::UI::GUIBuilder::gbSceneInfoOverlay(camera);
		Miasma::UI::GUIBuilder::gbSceneGraph(scene);
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

void GLRenderer::RenderSprite(std::unique_ptr<IScene>& scene, std::shared_ptr<GameObject> gameObject)
{
	// get the camera 
	tdogl::Camera camera = scene->GetCamera()->GetComponent<Camera>();
	Sprite2D& sprite2D = (*gameObject).GetComponent<Sprite2D>();
	MIASMA_ASSERT(&sprite2D != nullptr && "RenderSprite() is trying to draw a null Sprite2D");
	// use the current shader of the object
	glUseProgram(sprite2D.GetMaterial().GetShader().shaderId);

	// setup texture (get texture location "textureSample")
	glUniform1i(glGetUniformLocation(sprite2D.GetMaterial().GetShader().shaderId, "textureSample"), 0);
	// update camera transform 
	glUniformMatrix4fv(glGetUniformLocation(sprite2D.GetMaterial().GetShader().shaderId, "viewproj"), 1, false, glm::value_ptr(camera.orthomatrix()));

	// save current position
	glm::vec3 currentPosition = sprite2D.gameObject->transform.GetPosition();
	sprite2D.gameObject->transform = glm::identity<glm::mat4>();
	// translate to sprites position 
	sprite2D.gameObject->transform.translate(currentPosition);
	// rotate and center
	glm::vec2 spriteSize = sprite2D.GetSpriteSize();
	sprite2D.gameObject->transform.translate(glm::vec3(0.5f * spriteSize.x, 0.5f * spriteSize.y, 0.0f));
	sprite2D.gameObject->transform = glm::rotate(sprite2D.gameObject->transform.GetTransform(), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	sprite2D.gameObject->transform.translate(glm::vec3(-0.5f * spriteSize.x, -0.5f * spriteSize.y, 0.0f));
	//
	//// scale the sprite to size
	sprite2D.gameObject->transform = glm::scale(sprite2D.gameObject->transform.GetTransform(), glm::vec3(spriteSize, 1.0f));

	// set the model transform and sprite2D information
	glUniformMatrix4fv(glGetUniformLocation(sprite2D.GetMaterial().GetShader().shaderId, "model"), 1, false, glm::value_ptr(gameObject->transform.GetTransform()));
	glBindTextureUnit(0, sprite2D.GetMaterial().GetTextureId());
	glBindVertexArray(sprite2D.GetVertexArrayObject());
	glBindBuffer(GL_ARRAY_BUFFER, sprite2D.GetVertexBufferObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite2D.GetIndexBufferObject());

	glDrawElements(GL_TRIANGLES, (GLsizei)sprite2D.GetIndicesCount(), GL_UNSIGNED_INT, 0);
}

void GLRenderer::Shutdown()
{
	Miasma::UI::GUIBuilder::gbShutdownGUI();
	gltTerminate();
}

void GLRenderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}