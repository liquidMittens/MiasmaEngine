#include "BoxCollider2D.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
#include "CollisionBody2D.h"
#include "RigidBody2D.h"
using namespace Miasma::Component;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, BoxCollider2D);

BoxCollider2D::BoxCollider2D(GameObject* owner, glm::vec2 size) : 
	Component(owner, TO_STRING(BoxCollider2D))
{
	// try to get the body pointer from this object
	RigidBody2D& rigidBody = gameObject->GetComponent<RigidBody2D>();
	if (&rigidBody != nullptr) {
		b2PolygonShape boxShape;
		boxShape.SetAsBox(size.x, size.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		rigidBody.GetCollisionBody2D()->CreateFixture(&fixtureDef);
	}
}

BoxCollider2D::~BoxCollider2D()
{

}

// behavior functions
void BoxCollider2D::Start()
{

}

void BoxCollider2D::Update(float dt)
{

}

void BoxCollider2D::Shutdown()
{

}