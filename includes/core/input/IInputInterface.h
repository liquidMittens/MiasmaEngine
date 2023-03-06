#ifndef IINPUTINTERFACE_H_
#define IINPUTINTERFACE_H_

#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;

class IInputInterface
{
public:
	IInputInterface() = default;
	~IInputInterface() = default;

	virtual void Initialize() = 0;
	virtual void Update(GLFWwindow* pWindow, float frameTime) = 0;
	virtual void Update(GLFWwindow* pWindow, float frameTime, glm::vec3& position) = 0;
	virtual void Update(GLFWwindow* pWindow, float frameTime, glm::mat4& transform) = 0;
	virtual void Shutdown() = 0;

};

#endif
