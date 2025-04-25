#include "MoveObjectKeyboard.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include "GLFW/glfw3.h"

using namespace Miasma::Component;

CLASS_DEFINITION(Component, MoveObjectKeyboard);

MoveObjectKeyboard::MoveObjectKeyboard(GameObject* owner, GLFWwindow* pWindow, float moveSpeed) :
	Component(owner, TO_STRING(MoveObjectKeyboard)),
	m_glfwWindow(pWindow),
	m_moveSpeed(moveSpeed)
{
}

MoveObjectKeyboard::~MoveObjectKeyboard() {

}

void MoveObjectKeyboard::Start()
{

}

void MoveObjectKeyboard::Update(float dt)
{
	glm::vec3 position = gameObject->transform.GetPosition();
	
	//move position of camera based on WASD keys, and XZ keys for up and down
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_W)) {
		float moveZ = position.z - (m_moveSpeed * dt);
		position.z = moveZ;
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_A)) {
		float moveX = position.x - (m_moveSpeed * dt);
		position.x = moveX;
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_S)) {
		float moveZ = position.z + (m_moveSpeed * dt);
		position.z = moveZ;
	}
	if (glfwGetKey(m_glfwWindow, GLFW_KEY_D)) {
		float moveX = position.x + (m_moveSpeed * dt);
		position.x = moveX;
	}

	gameObject->transform.SetPosition(position);
}

void MoveObjectKeyboard::Shutdown()
{

}