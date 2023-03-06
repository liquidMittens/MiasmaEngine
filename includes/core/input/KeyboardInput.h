#ifndef KEYBOARDINPUT
#define KEYBOARDINPUT
#include "input\IInputInterface.h"
#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;

class KeyboardInput : public IInputInterface
{
public: 
	
	void Initialize() override;
	void Update(GLFWwindow* pWindow, float frameTime, glm::vec3& position) override;
	void Shutdown() override;

private:

};

#endif
