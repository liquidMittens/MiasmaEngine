#ifndef GLRENDERER_H_
#define GLRENDERER_H_
#include "rendering/IRenderInterface.h"
#include <vector>
#include <memory>
#include "objects/GameObject.h"
#include "Sprite2D.h"
#include "camera/Camera.h"
using namespace tdogl;

class IScene;
struct GLFWwindow;

namespace Miasma::Renderer
{

	struct LightShaderInformation {
		unsigned int position;
		unsigned int color;
		unsigned int strength;
	};

	class GLRenderer : public Miasma::Renderer::IRenderInterface
	{
	public:
		GLRenderer();
		~GLRenderer();

		// Inherited via IRenderInterface
		virtual void Initialize(GLWindow* pWindow) override;
		virtual void DrawTextObjects(Miasma::Component::Text* textComponent) override;
		virtual bool DrawScene(std::unique_ptr<IScene>& scene) override;
		virtual void Shutdown() override;

		// window resize callback
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	private:
		void RenderSprite(std::unique_ptr<IScene>& scene, std::shared_ptr<GameObject> gameObject);
	};
}
#endif
