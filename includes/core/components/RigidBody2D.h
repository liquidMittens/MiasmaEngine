#ifndef RIGIDBODY2D_H_
#define RIGIDBODY2D_H_
#include "Component.h"
#include "box2d.h"
#include "glm/glm.hpp"

namespace Miasma::Component
{

	class RigidBody2D : public Component
	{
	public:
		CLASS_DECLARATION(RigidBody2D);

		RigidBody2D(GameObject* owner, glm::vec2 pos);
		~RigidBody2D();

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		b2Body* GetCollisionBody2D() { return m_rigidBody2D; }

	private:
		b2Body* m_rigidBody2D;
	};
}

#endif
