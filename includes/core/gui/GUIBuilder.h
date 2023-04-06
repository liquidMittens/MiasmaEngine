#ifndef GUIBUILDER_H_
#define GUIBUILDER_H_
#include <memory>
#include "camera/Camera.h"
using namespace tdogl;

struct GLFWwindow;
class Scene;

constexpr auto SliderTransformMin = -20.0f;
constexpr auto SliderTransformMax = 25.0f;

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
	static void gbSceneInfoOverlay(std::shared_ptr<tdogl::Camera>& camera);
	static void gbSceneObjectsInfo(std::unique_ptr<Scene>& scene);
	static void gbShowImGuiDemoWindow();
};

#endif
