#include "RigidBody2D.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
using namespace Miasma::Component;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, RigidBody2D);

RigidBody2D::RigidBody2D(GameObject* owner, glm::vec2 pos) : 
	Component(owner, TO_STRING(RigidBody2D)), 
	m_rigidBody2D(nullptr)
{
	b2BodyDef rigidBodyDef;
	rigidBodyDef.type = b2_dynamicBody;
	rigidBodyDef.position.Set(pos.x, pos.y);
	m_rigidBody2D = PhysicsController::GetInstance().GetPhysics2DWorld()->CreateBody(&rigidBodyDef);
}

RigidBody2D::~RigidBody2D()
{

}

// behavior functions
void RigidBody2D::Start()
{

}

void RigidBody2D::Update(float dt)
{
	b2Vec2 rigidBodyPosition = m_rigidBody2D->GetPosition();
	gameObject->transform.SetPosition(rigidBodyPosition.x, rigidBodyPosition.y, 1.0f);
}

void RigidBody2D::Shutdown()
{

}