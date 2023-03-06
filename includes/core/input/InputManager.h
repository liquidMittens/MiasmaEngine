#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <vector>
#include <memory>

class IInputInterface;
struct GLFWwindow;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void AddInputInterface(std::unique_ptr<IInputInterface> newInterface);
	void UpdateInput(GLFWwindow* pWindow, float frameTime);
	void Shutdown();

private:
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	unsigned int m_currentInputInterface;
	std::vector<std::unique_ptr<IInputInterface>> m_inputInterfaceList;
};

#endif
