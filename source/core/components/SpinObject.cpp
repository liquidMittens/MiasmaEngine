#include "components/SpinObject.h"
#include "objects/GameObject.h"
using namespace Miasma::Component;

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
		gameObject->transform.resetTransformMatrix();
	}
}

void SpinObject::Update(float dt)
{
	if (gameObject != nullptr) {
		glm::mat4 matrix = glm::identity<glm::mat4>();
		gameObject->transform.rotate(dt * m_spinSpeed, { 0.0f, 1.0f, 0.0f });
	}
}

void SpinObject::Shutdown()
{

}