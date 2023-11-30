#include "BoxCollider2D.h"
#include "objects/GameObject.h"
#include "physics/PhysicsController.h"
#include "CollisionBody2D.h"
#include "RigidBody2D.h"
#include "Sprite2D.h"
#include "util.h"
using namespace Miasma::Component;
using namespace Miasma::Physics;

CLASS_DEFINITION(Component, BoxCollider2D);

BoxCollider2D::BoxCollider2D(GameObject* owner) : 
	Component(owner, TO_STRING(BoxCollider2D))
{
	// try to get the body pointer from this object
	RigidBody2D& rigidBody = gameObject->GetComponent<RigidBody2D>();
	CollisionBody2D& collisionBody = gameObject->GetComponent<CollisionBody2D>();
	MIASMA_ASSERT((&rigidBody != nullptr || &collisionBody != nullptr) && "BoxCollider2D needs at least one Body2D component");
	if (&rigidBody != nullptr) {
		// get the sprite2D component from the gameObject
		Sprite2D& sprite = gameObject->GetComponent<Sprite2D>();
		MIASMA_ASSERT(&sprite != nullptr && "BoxCollider2D gameObject must have a Sprite2D component");
		b2PolygonShape boxShape;
		boxShape.SetAsBox(sprite.GetSpriteSize().x / 2.0f, sprite.GetSpriteSize().y / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 5.0f;
		fixtureDef.friction = 0.1f;

		rigidBody.GetCollisionBody2D()->CreateFixture(&fixtureDef);
	}
	else if (&collisionBody != nullptr) {
		Sprite2D& sprite = gameObject->GetComponent<Sprite2D>();
		MIASMA_ASSERT(&sprite != nullptr && "BoxCollider2D gameObject must have a Sprite2D component");
		b2PolygonShape boxShape;
		boxShape.SetAsBox(sprite.GetSpriteSize().x / 2.0f, sprite.GetSpriteSize().y / 2.0f);
		collisionBody.GetCollisionBody2D()->CreateFixture(&boxShape, 0.0f);
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