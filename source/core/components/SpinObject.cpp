#include "components/SpinObject.h"
#include "objects/GameObject.h"
using namespace miasma_rtti;

CLASS_DEFINITION(Component, SpinObject);

SpinObject::SpinObject(GameObject* owner, float spinSpeed) :
	Component(owner, TO_STRING(SpinObject)),
	m_spinSpeed(spinSpeed)
{

}

SpinObject::~SpinObject()
{
	
}

// behavior functions
void SpinObject::Start()
{
	if (gameObject != nullptr) {
		glm::mat4 matrix = glm::identity<glm::mat4>();
		matrix = glm::rotate(gameObject->transform.GetTransform(), -45.5f, { 1.0f, 0.0f, 0.0f });
		gameObject->transform.GetTransform() = matrix;
	}
}

void SpinObject::Update(float dt)
{
	if (gameObject != nullptr) {
		glm::mat4 matrix = glm::identity<glm::mat4>();
		matrix = glm::rotate(gameObject->transform.GetTransform(), dt * m_spinSpeed, { 0.0f, 0.0f, 1.0f });
		gameObject->transform.GetTransform() = matrix;
	}
}

void SpinObject::Shutdown()
{

}