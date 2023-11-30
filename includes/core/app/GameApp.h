#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include <memory>
#include "core/rendering/GLRenderer.h"
#include "core/rendering/GLRenderer2D.h"
using namespace Miasma::Renderer;
#include "physics/PhysicsController.h"
#include <GLFW/glfw3.h>
using namespace Miasma::Physics;

struct GLFWwindow;
class GLWindow;
class IScene;

class GameApp
{
public:
	GameApp();
	~GameApp();

	void InitializeGameApp();
	void RunGameAppLoop();
	void ShutdownGameApp();

private:
	std::unique_ptr<GLWindow> m_glWindow;
	std::unique_ptr<Miasma::Renderer::GLRenderer> m_renderer;
	std::unique_ptr<Miasma::Renderer::GLRenderer2D> m_renderer2D;
	static std::unique_ptr<IScene> m_currentScene;
	
	// variables for calculating framerate
	// fps counter
	double m_lastTime, m_currentTime;
	int m_numFrames;
	float m_frameTime;
	double m_deltaTime;
	bool m_render2DMode;

	void calculateFrameRate();
};

#endif