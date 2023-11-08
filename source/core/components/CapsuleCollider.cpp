#include "CapsuleCollider.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
using namespace Miasma::RTTI;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, CapsuleCollider);

CapsuleCollider::CapsuleCollider(GameObject* owner, float radius, float height) :
	Component(owner, TO_STRING(CapsuleCollider)),
	m_capsuleShape(nullptr),
	m_collider(nullptr)
{
	// try to get any body component
	CollisionBody& body = owner->GetComponent<CollisionBody>();
	RigidBody& rigidBody = owner->GetComponent<RigidBody>();
	if (&body != nullptr) {
		m_capsuleShape = PhysicsController::GetInstance().GetPhysicsCommon().createCapsuleShape(radius, height);
		m_collider = body.GetCollider()->addCollider(m_capsuleShape, rp3d::Transform::identity());
	}
	else if (&rigidBody != nullptr) {
		m_capsuleShape = PhysicsController::GetInstance().GetPhysicsCommon().createCapsuleShape(radius, height);
		m_collider = rigidBody.GetCollider()->addCollider(m_capsuleShape, rp3d::Transform::identity());
	}
}

CapsuleCollider::~CapsuleCollider()
{

}

void CapsuleCollider::Start()
{

}

void CapsuleCollider::Update(float dt)
{

}

void CapsuleCollider::Shutdown()
{

}