#ifndef OGLWINDOW_H_
#define OGLWINDOW_H_

#include <memory>
#include <glm/glm.hpp>

struct GLFWwindow;
struct GLFWcursor;
class Scene;
class GLRenderer;

class GLWindow
{
public:
	GLWindow();
	~GLWindow();

	bool CreateGLWindow();
	void ExecuteGLWindowLoop();
	void ShutdownGLWindow();

private:

	bool InitGLWindow();
	bool InitGLFWCursor();
	void calculateFrameRate();

	// OGLWindows have (at minimum): 
	// - a GLFWwindow
	// - a OGLRenderer
	// - a Scene
	GLFWwindow* m_window;
	std::unique_ptr<Scene> m_scene;
	std::unique_ptr<GLRenderer> m_renderer;
	// cursor obj
	GLFWcursor* m_cursor;
	// variables for calculating framerate
	// fps counter
	double m_lastTime, m_currentTime;
	int m_numFrames;
	float m_frameTime;
	double m_deltaTime;
};

#endif
