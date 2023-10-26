#ifndef GLRENDERER2D_H_
#define GLRENDERER2D_H_
#include "rendering/IRenderInterface.h"
#include <vector>
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

class Scene;
struct GLFWwindow;

namespace Miasma::Renderer
{
	class GLRenderer2D : public Miasma::Renderer::IRenderInterface
	{
	public:
		GLRenderer2D() = default;
		~GLRenderer2D() = default;

		// Inherited via IRenderInterface
		virtual void Initialize(GLWindow* pWindow, std::shared_ptr<tdogl::Camera> camera) override;
		virtual bool DrawScene(std::unique_ptr<Scene>& scene) override;
		virtual void Shutdown() override;

		// window resize callback
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	private:
		std::shared_ptr<tdogl::Camera> m_camera;
	};
}

#endif