#include "components/BoxCollider.h"
#include "components/CollisionBody.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
using namespace Miasma::RTTI;
using namespace Miasma::Physics;

CLASS_DEFINITION(Collider, BoxCollider);

BoxCollider::BoxCollider(GameObject* owner, glm::vec3 halfExtents) :
	Collider(owner, TO_STRING(BoxCollider)),
	m_boxShape(nullptr),
	m_collider(nullptr)
{
	// try to get any body component
	CollisionBody& body = owner->GetComponent<CollisionBody>();
	RigidBody& rigidBody = owner->GetComponent<RigidBody>();
	if (&body != nullptr) {
		m_boxShape = PhysicsController::GetInstance().GetPhysicsCommon().createBoxShape(rp3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z));
		m_collider = body.GetCollider()->addCollider(m_boxShape, rp3d::Transform::identity());
	}
	else if (&rigidBody != nullptr) {
		m_boxShape = PhysicsController::GetInstance().GetPhysicsCommon().createBoxShape(rp3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z));
		m_collider = rigidBody.GetCollider()->addCollider(m_boxShape, rp3d::Transform::identity());
	}
	
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Start()
{

}

void BoxCollider::Update(float dt)
{

}

void BoxCollider::Shutdown()
{

}