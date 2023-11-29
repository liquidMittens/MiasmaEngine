#include "CollisionBody2D.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
using namespace Miasma::Component;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, CollisionBody2D);

CollisionBody2D::CollisionBody2D(GameObject* owner, glm::vec2 pos) :
	Component(owner, TO_STRING(CollisionBody2D)),
	m_collisionBody2D(nullptr)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x, pos.y);
	m_collisionBody2D = PhysicsController::GetInstance().GetPhysics2DWorld()->CreateBody(&bodyDef);
}

CollisionBody2D::~CollisionBody2D()
{

}

void CollisionBody2D::Start()
{

}

void CollisionBody2D::Update(float dt)
{
	gameObject->transform.SetPosition(m_collisionBody2D->GetPosition().x, m_collisionBody2D->GetPosition().y, 1.0f);
}

void CollisionBody2D::Shutdown()
{

}
