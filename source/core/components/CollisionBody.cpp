#include "components/CollisionBody.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
#include <iostream>
using namespace Miasma::RTTI;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, CollisionBody);

CollisionBody::CollisionBody(GameObject* owner) : 
	Component(owner, TO_STRING(CollisionBody))
{
	rp3d::Vector3 initialPos(owner->transform.GetPosition().x, owner->transform.GetPosition().y, owner->transform.GetPosition().z);
	rp3d::Quaternion initialRotation = rp3d::Quaternion::identity();
	rp3d::Transform initialTransform(initialPos, initialRotation);
	m_transform = initialTransform;
	m_collisionBody = PhysicsController::GetInstance().GetPhysicsWorld()->createCollisionBody(m_transform);
	if (m_collisionBody != nullptr) {
		PhysicsController::GetInstance().AddBodyToList(this);
	}
}

CollisionBody::~CollisionBody()
{

}

// behavior functions
void CollisionBody::Start()
{

}

void CollisionBody::Update(float dt)
{
	// update the collision body to the gameObjects transform every frame
	rp3d::Vector3 newPos(gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y, gameObject->transform.GetPosition().z);
	rp3d::Quaternion newRotation = rp3d::Quaternion::identity();
	rp3d::Transform newTransform(newPos, newRotation);
	m_transform = newTransform;

	// set transform
	//m_collisionBody->setTransform(newTransform);
	//std::cout << std::format("{}: pos: ({},{},{})\n", gameObject->tag, newTransform.getPosition().x, newTransform.getPosition().y, newTransform.getPosition().z);
}

void CollisionBody::Shutdown()
{

}