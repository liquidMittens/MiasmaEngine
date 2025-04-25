#include "components/RigidBody.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
#include <iostream>
using namespace Miasma::Component;
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
		m_rigidBody->setMass(rp3d::decimal(150.0));
		m_rigidBody->setLinearDamping(rp3d::decimal(5.0));
		m_rigidBody->setAngularDamping(rp3d::decimal(0.0));
		m_rigidBody->setLinearLockAxisFactor(rp3d::Vector3(1.0f, 1.0f, 1.0f));
		m_rigidBody->setAngularLockAxisFactor(rp3d::Vector3(0.0f, 0.0f, 0.0f));
		PhysicsController::GetInstance().AddRigidBodyToList(this);
	}
}

RigidBody::~RigidBody()
{
	PhysicsController::GetInstance().GetPhysicsWorld()->destroyRigidBody(m_rigidBody);
	m_rigidBody = nullptr;
}

// behavior functions
void RigidBody::Start()
{

}

void RigidBody::Update(float dt)
{
	if (m_rigidBody->getType() == rp3d::BodyType::DYNAMIC) {
		// update the collision body to the gameObjects transform every frame
		//rp3d::Vector3 newPos(gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y, gameObject->transform.GetPosition().z);
		rp3d::Vector3 newPos = m_rigidBody->getTransform().getPosition();
		rp3d::Quaternion newRotation = m_rigidBody->getTransform().getOrientation();
		rp3d::Transform newTransform(newPos, newRotation);
		float matrix[16];
		m_rigidBody->getTransform().getOpenGLMatrix(matrix);

		// Constant physics time step
		const float timeStep = 1.0f / 60.0f;
		rp3d::decimal factor = rp3d::decimal(PhysicsController::GetInstance().GetAccumulator()) / timeStep;
		// Compute the interpolated transform of the rigid body
		rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(m_previousTransform, newTransform, factor);
		
		// update the gameobjects transform from the rigidbody
		gameObject->transform.SetPosition(interpolatedTransform.getPosition().x, interpolatedTransform.getPosition().y, interpolatedTransform.getPosition().z);
		//std::cout << std::format("RigidBody({}:{}): pos: ({},{},{})\n", gameObject->tag, "Dynamic", newPos.x, newPos.y, newPos.z);
		m_previousTransform = newTransform;
	}
	else if (m_rigidBody->getType() == rp3d::BodyType::STATIC) {
		rp3d::Vector3 newPos = m_rigidBody->getTransform().getPosition();
		//std::cout << std::format("RigidBody({}:{}): pos: ({},{},{})\n", gameObject->tag, "Static", newPos.x, newPos.y, newPos.z);
	}
}

void RigidBody::Shutdown()
{

}

void RigidBody::UpdateTransformPosition(glm::vec3 pos)
{
	if (m_rigidBody != nullptr) {
		rp3d::Vector3 offset(pos.x, pos.y, pos.z);
		rp3d::Quaternion orientation = rp3d::Quaternion::identity();
		rp3d::Transform newTransform(offset, orientation);
		m_rigidBody->setTransform(newTransform);
	}
}

void RigidBody::ApplyForce(rp3d::Vector3 force)
{
	if (m_rigidBody != nullptr) {
		rp3d::Vector3 currentForce = m_rigidBody->getForce(); 
		std::cout << std::format("Camera force: {},{},{}\n", m_rigidBody->getForce().x, m_rigidBody->getForce().y, m_rigidBody->getForce().z);
		m_rigidBody->applyLocalForceAtCenterOfMass(force);
	}
}

void RigidBody::ResetForce()
{
	if (m_rigidBody != nullptr) {
		m_rigidBody->setLinearVelocity(rp3d::Vector3(0.0f, 0.0f, 0.0f));
	}
}