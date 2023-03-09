#ifndef GUIBUILDER_H_
#define GUIBUILDER_H_
#include <memory>

struct GLFWwindow;
class Scene;

#define GUI_TEXT_RED ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
#define GUI_TEXT_GREEN ImVec4(0.0f, 1.0f, 0.0f, 1.0f)
#define GUI_TEXT_BLUE ImVec4(0.0f, 0.0f, 1.0f, 1.0f)
#define GUI_TEXT_BLACK ImVec4(0.0f, 0.0f, 0.0f, 1.0f)

class GUIBuilder
{
public:
	static void gbInitializeGUI(GLFWwindow* pWindow);
	static void gbFeedInput();
	static void gbRenderGUI();
	static void gbShutdownGUI();

	// windows
	static void gbTestWindow();
	static void gbSceneInfoOverlay();
	static void gbSceneObjectsInfo(std::unique_ptr<Scene>& scene);
	static void gbShowImGuiDemoWindow();
};

#endif
