#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "rendering/IRenderInterface.h"
#include <vector>
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

class Scene;
struct GLFWwindow;

struct LightShaderInformation {
	unsigned int position;
	unsigned int color;
	unsigned int strength;
};

class GLRenderer : public IRenderInterface
{
public:
	// Inherited via IRenderInterface
	virtual void Initialize(GLWindow* pWindow, std::shared_ptr<tdogl::Camera> camera) override;
	virtual bool DrawScene(std::unique_ptr<Scene>& scene) override;
	virtual void Shutdown() override;

	// window resize callback
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
private:
	std::shared_ptr<tdogl::Camera> m_camera;
	LightShaderInformation m_lightShaderInfo;
	unsigned int m_cameraShaderPos;
};

#endif
