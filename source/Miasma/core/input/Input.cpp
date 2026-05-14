#include <Miasma/core/input/Input.h>
using namespace Miasma::Input;

std::unique_ptr<Input> Input::mInstance = nullptr;

Input::Input() {

}

Input::~Input() {

}

Input& Input::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = std::make_unique<Input>();
	}
	return *mInstance.get();
}

void Input::GetKey(int keyCode)
{
	
}

void Input::GetKeyDown(int keyCode)
{

}

void Input::GetKeyUp(int keyCode)
{

}