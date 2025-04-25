#ifndef MOVEOBJECTKEYBOARD_H_
#define MOVEOBJECTKEYBOARD_H_
#include "Component.h"

struct GLFWwindow;

namespace Miasma::Component
{
	class MoveObjectKeyboard : public Component
	{
	public: 
		CLASS_DECLARATION(MoveObjectKeyboard);

		MoveObjectKeyboard(GameObject* owner, GLFWwindow* pWindow, float moveSpeed);
		~MoveObjectKeyboard();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

	private:
		float m_moveSpeed;
		GLFWwindow* m_glfwWindow;

	};
}


#endif