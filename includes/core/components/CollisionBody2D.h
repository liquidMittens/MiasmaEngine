#ifndef COLLISIONBODY2D_H_
#define COLLISIONBODY2D_H_
#include "Component.h"
#include "box2d.h"
#include "glm/glm.hpp"

namespace Miasma::Component
{
	class CollisionBody2D : public Component
	{
	public:

		CLASS_DECLARATION(CollisionBody2D);

		CollisionBody2D(GameObject* owner, glm::vec2 pos);
		~CollisionBody2D();

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		b2Body* GetCollisionBody2D() { return m_collisionBody2D; }

	private: 
		b2Body* m_collisionBody2D;
	};
}

#endif
