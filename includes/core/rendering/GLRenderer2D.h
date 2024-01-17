#ifndef GLRENDERER2D_H_
#define GLRENDERER2D_H_
#include "rendering/IRenderInterface.h"
#include <vector>
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

class IScene;
struct GLFWwindow;

namespace Miasma::Renderer
{
	class GLRenderer2D : public Miasma::Renderer::IRenderInterface
	{
	public:
		GLRenderer2D();
		~GLRenderer2D();

		// Inherited via IRenderInterface
		virtual void Initialize(GLWindow* pWindow) override;
		virtual void DrawTextObjects(Miasma::Component::Text* textComponent) override;
		virtual bool DrawScene(std::unique_ptr<IScene>& scene) override;
		virtual void Shutdown() override;

		// window resize callback
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	private:

	};
}

#endif