#ifndef FPSCAMERAMOVEMENT_H_
#define FPSCAMERAMOVEMENT_H_
#include "Component.h"
#include "glm/glm.hpp"

struct GLFWwindow;

namespace Miasma::Component
{
	constexpr float moveSpeed = 2500.0;
	constexpr float jumpForce = 100000.0;
	constexpr float zoomSensitivity = -0.5f;

	class FPSCameraMovement : public Component
	{
	public: 
		CLASS_DECLARATION(FPSCameraMovement);

		FPSCameraMovement(GameObject* owner, GLFWwindow* pWindow);
		~FPSCameraMovement();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:
		GLFWwindow* m_glfwWindow;
		bool m_wireframe;
		static double m_scrollY;
		static bool m_mouseModeEnabled;

		static void OnScroll(GLFWwindow* window, double deltaX, double deltaY);
		static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
	};
}

#endif
