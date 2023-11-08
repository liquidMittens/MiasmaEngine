#include "components/RigidBody.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
#include <iostream>
using namespace Miasma::RTTI;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, RigidBody);

RigidBody::RigidBody(GameObject* owner, rp3d::BodyType type) :
	Component(owner, TO_STRING(RigidBody)),
	m_rigidBody(nullptr)
{
	rp3d::Vector3 initialPos(owner->transform.GetPosition().x, owner->transform.GetPosition().y, owner->transform.GetPosition().z);
	rp3d::Quaternion initialRotation = rp3d::Quaternion::identity();
	rp3d::Transform initialTransform(initialPos, initialRotation);
	//m_transform = initialTransform;
	m_rigidBody = PhysicsController::GetInstance().GetPhysicsWorld()->createRigidBody(initialTransform);
	if (m_rigidBody != nullptr) {
		m_rigidBody->setType(type);
		PhysicsController::GetInstance().AddRigidBodyToList(this);
	}
}

RigidBody::~RigidBody()
{

}

// behavior functions
void RigidBody::Start()
{

}

void RigidBody::Update(float dt)
{
	// update the collision body to the gameObjects transform every frame
	//rp3d::Vector3 newPos(gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y, gameObject->transform.GetPosition().z);
	rp3d::Vector3 newPos = m_rigidBody->getTransform().getPosition();
	rp3d::Quaternion newRotation = rp3d::Quaternion::identity();
	rp3d::Transform newTransform(newPos, newRotation);
	//m_transform = newTransform;
	// update the gameobjects transform from the rigidbody
	gameObject->transform.SetPosition(newPos.x, newPos.y, newPos.z);
	std::cout << std::format("{}: pos: ({},{},{})\n", gameObject->tag, newTransform.getPosition().x, newTransform.getPosition().y, newTransform.getPosition().z);
}

void RigidBody::Shutdown()
{

}