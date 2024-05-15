#include "rendering/GLRenderer2D.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#define GLT_IMPLEMENTATION
#include "glText/gltext.h"
#include "glm/gtc/type_ptr.hpp"
#include "objects/GameObject.h"
#include "components/Sprite2D.h"
#include "components/AnimatedSprite2D.h"
#include "Text.h"
#include "camera/Camera.h"
#include "model/IScene.h"
#include "app/GLWindow.h"
#include "gui/GUIBuilder.h"
#include <iostream>
#include <sstream>
using namespace Miasma::Renderer;


GLRenderer2D::GLRenderer2D()
{

}

GLRenderer2D::~GLRenderer2D()
{

}

// Inherited via IRenderInterface
void GLRenderer2D::Initialize(GLWindow* pWindow)
{
	// set up framebuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSetFramebufferSizeCallback(pWindow->GetGLFWWindow(), GLRenderer2D::framebuffer_size_callback);
	gltInit();
}

void GLRenderer2D::DrawTextObjects(Miasma::Component::Text* textComponent)
{
	gltBeginDraw();
	gltColor(textComponent->GetTextColor().x, textComponent->GetTextColor().y, textComponent->GetTextColor().z, 1.0f);
	gltDrawText2D(textComponent->GetGLTtext(), textComponent->gameObject->transform.GetPosition().x, textComponent->gameObject->transform.GetPosition().y, textComponent->GetTextScale());
	gltEndDraw();
}

bool GLRenderer2D::DrawScene(std::unique_ptr<IScene>& scene)
{
	bool drewFrame = true;
	if (scene) {
		// get the camera 
		tdogl::Camera camera = scene->GetCamera()->GetComponent<Camera>();
		// clear buffer and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		GUIBuilder::gbFeedInput();

		// loop through and render all of our meshes
		for (auto& gameObject : scene->GetGameObjectsList()) {
			Miasma::Component::Sprite2D& sprite2D = gameObject->GetComponent<Miasma::Component::Sprite2D>();
			Miasma::Component::AnimatedSprite2D& animatedSprite = gameObject->GetComponent<AnimatedSprite2D>();
			Miasma::Component::Text& textComponent = gameObject->GetComponent<Miasma::Component::Text>();
			
			if (!gameObject->IsActive()) {
				continue;
			}

			// sprite2D and animated sprite rendering
			if (&sprite2D != nullptr) {
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

				// set frame Index uniform if we have a valid animated sprite
				if (&animatedSprite != nullptr && !animatedSprite.IsAnimationFinished()) {
					glUniform1i(glGetUniformLocation(animatedSprite.GetMaterial().GetShader().shaderId, "currentFrameIndex"), animatedSprite.GetCurrentFrameIndex());
					glUniform1i(glGetUniformLocation(animatedSprite.GetMaterial().GetShader().shaderId, "MAX_COLUMNS"), animatedSprite.GetAnimationInfo().frameSizeX);
					glUniform1i(glGetUniformLocation(animatedSprite.GetMaterial().GetShader().shaderId, "MAX_ROWS"), animatedSprite.GetAnimationInfo().frameSizeY);
					std::cout << std::format("Current Frame: {}\n", animatedSprite.GetCurrentFrameIndex());
				}

				// set the model transform and sprite2D information
				glUniformMatrix4fv(glGetUniformLocation(sprite2D.GetMaterial().GetShader().shaderId, "model"), 1, false, glm::value_ptr(gameObject->transform.GetTransform()));
				glBindTextureUnit(0, sprite2D.GetMaterial().GetTextureId());
				glBindVertexArray(sprite2D.GetVertexArrayObject());
				glBindBuffer(GL_ARRAY_BUFFER, sprite2D.GetVertexBufferObject());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite2D.GetIndexBufferObject());

				glDrawElements(GL_TRIANGLES, (GLsizei)sprite2D.GetIndicesCount(), GL_UNSIGNED_INT, 0);
			}
			// text rendering
			if (&textComponent != nullptr) {
				DrawTextObjects(&textComponent);
			}
		}
		GUIBuilder::gbSceneGraph(scene);
		GUIBuilder::gbRenderGUI();
	}
	else {
		if (!scene) {
			std::cout << "ERROR: GLRenderer scene is NULL\n";
			drewFrame = false;
		}
	}

	return drewFrame;
}

void GLRenderer2D::Shutdown()
{
	gltTerminate();	
}

void GLRenderer2D::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}