#include "input/InputManager.h"
#include "input/IInputInterface.h"
#include "GLFW/glfw3.h"

InputManager::InputManager() :
	m_currentInputInterface(0)
{

}

InputManager::~InputManager()
{
	
}

void InputManager::AddInputInterface(std::unique_ptr<IInputInterface> newInterface)
{
	if (newInterface) {
		newInterface->Initialize();
		m_inputInterfaceList.push_back(std::move(newInterface));
	}
}

void InputManager::UpdateInput(GLFWwindow* pWindow, float frameTime)
{
	if (m_inputInterfaceList[m_currentInputInterface]) {
		m_inputInterfaceList[m_currentInputInterface]->Update(pWindow, frameTime);
	}
}

void InputManager::Shutdown()
{
	for (auto& interfaceObject : m_inputInterfaceList) {
		interfaceObject->Shutdown();
	}
}