#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include <memory>
#include "core/rendering/GLRenderer.h"
#include "core/rendering/GLRenderer2D.h"
using namespace Miasma::Renderer;
#include "physics/PhysicsController.h"
using namespace Miasma::Physics;

struct GLFWwindow;
class GLWindow;
class Scene;

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
	std::unique_ptr<Scene> m_currentScene;
	std::unique_ptr<Miasma::Renderer::GLRenderer> m_renderer;
	std::unique_ptr<Miasma::Renderer::GLRenderer2D> m_renderer2D;
	
	// variables for calculating framerate
	// fps counter
	double m_lastTime, m_currentTime;
	int m_numFrames;
	float m_frameTime;
	double m_deltaTime;

	// camera info
	bool m_wireframe = false;
	static double m_scrollY;
	static bool m_mouseModeEnabled;

	void calculateFrameRate();
	void ProcessInput(GLFWwindow* pWindow, float frameTime);
	static void OnScroll(GLFWwindow* window, double deltaX, double deltaY);
	static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
};

#endif