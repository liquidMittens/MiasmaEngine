#include "FPSCameraMovement.h"
#include "camera/Camera.h"
#include "objects/GameObject.h"
#include "RigidBody.h"
#include "GLFW/glfw3.h"
using namespace tdogl;
using namespace Miasma::Component;


CLASS_DEFINITION(Component, FPSCameraMovement);

double FPSCameraMovement::m_scrollY = 0.0;
bool FPSCameraMovement::m_mouseModeEnabled = false;

FPSCameraMovement::FPSCameraMovement(GameObject* owner, GLFWwindow* pWindow) :
	Component(owner, TO_STRING(FPSCameraMovement)), 
	m_glfwWindow(pWindow),
	m_wireframe(false)
{
	// register callbacks 
	glfwSetScrollCallback(m_glfwWindow, FPSCameraMovement::OnScroll);
	glfwSetMouseButtonCallback(m_glfwWindow, FPSCameraMovement::OnMouseButton);
	//glfwSetKeyCallback(m_glfwWindow, FPSCameraMovement::key_callback);
}

FPSCameraMovement::~FPSCameraMovement()
{

}

void FPSCameraMovement::Start()
{

}

void FPSCameraMovement::Update(float dt)
{
	if (m_glfwWindow != nullptr) {
		auto& camera = gameObject->GetComponent<Camera>();
		RigidBody& cameraBody = gameObject->GetComponent<RigidBody>();

		if (glfwGetKey(m_glfwWindow, GLFW_KEY_Q) == GLFW_PRESS) {
			m_wireframe = !m_wireframe;
		}

		glm::vec3 velocity(0.0f, 0.0f, 0.0f);
		//move position of camera based on WASD keys, and XZ keys for up and down
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_W)) {
			velocity.z += 1;
		}
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_A)) {
			velocity.x -= 1;
		}
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_S)) {
			velocity.z -= 1;
		}
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_D)) {
			velocity.x += 1;
		}

		if (velocity.x != 0.0f || velocity.z != 0.0f) {
			glm::vec3 normalizedVelocity = glm::normalize(velocity);
			glm::vec3 relativeDirection = (normalizedVelocity.z * camera.forward_novertical_axis() + normalizedVelocity.x * camera.right());
			velocity.x = relativeDirection.x * moveSpeed;
			velocity.z = relativeDirection.z * moveSpeed;
			if (&cameraBody != nullptr) {
				cameraBody.ApplyForce(rp3d::Vector3(velocity.x, 0.0, velocity.z));
			}
		}

		if (glfwGetKey(m_glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			auto& camera = gameObject->GetComponent<Camera>();
			RigidBody& cameraBody = gameObject->GetComponent<RigidBody>();
			rp3d::Vector3 jumpForceVec = jumpForce * rp3d::Vector3(0.0f, camera.up_novertical_axis().y, 0.0f);
			cameraBody.ApplyForce(jumpForceVec);
		}

		if (glfwGetKey(m_glfwWindow, GLFW_KEY_LEFT_CONTROL)) {
			camera.offsetPosition(dt * moveSpeed * -glm::vec3(0, 1, 0));
		}

		if (!m_mouseModeEnabled) {
			//rotate camera based on mouse movement
			const float mouseSensitivity = 0.1f;
			double mouseX, mouseY;
			glfwGetCursorPos(m_glfwWindow, &mouseX, &mouseY);
			camera.offsetOrientation(mouseSensitivity * (float)mouseY, mouseSensitivity * (float)mouseX);
			glfwSetCursorPos(m_glfwWindow, 0, 0); //reset the mouse, so it doesn't go out of the window

			//increase or decrease field of view based on mouse wheel
			float fieldOfView = camera.fieldOfView() + zoomSensitivity * (float)m_scrollY;
			if (fieldOfView < 5.0f) fieldOfView = 5.0f;
			if (fieldOfView > 130.0f) fieldOfView = 130.0f;
			camera.setFieldOfView(fieldOfView);
			m_scrollY = 0;
		}
	}
}

void FPSCameraMovement::Shutdown()
{

}

// records how far the y axis has been scrolled
void FPSCameraMovement::OnScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	m_scrollY += deltaY;
}

void FPSCameraMovement::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
		std::cout << "clicked mouse button right\n";
		m_mouseModeEnabled = !m_mouseModeEnabled;
		if (m_mouseModeEnabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}