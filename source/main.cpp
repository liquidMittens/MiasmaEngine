// main 
#include "app/GLWindow.h"

int main(int argc, char** argv)
{
	// create and execute out window loop
	GLWindow glWindow;
	if (glWindow.CreateGLWindow()) {
		glWindow.ExecuteGLWindowLoop();
		glWindow.ShutdownGLWindow();
	}
	return 0;
}