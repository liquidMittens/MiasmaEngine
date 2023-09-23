#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <memory>
#include <glm/glm.hpp>

struct GLFWwindow;
struct GLFWcursor;

class GLWindow
{
public:
	GLWindow();
	~GLWindow();

	bool CreateGLWindow();
	void ShutdownGLWindow();

	GLFWwindow* GetGLFWWindow() const { return m_window; }

private:

	bool InitGLWindow();
	bool InitGLFWCursor();

	// GLWindows have (at minimum): 
	// - a GLFWwindow
	GLFWwindow* m_window;
	// cursor obj
	GLFWcursor* m_cursor;
};

#endif
