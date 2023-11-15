#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"
#include "glm/glm.hpp"

namespace Miasma::RTTI
{
	class RigidBody : public Component
	{
	public:
		CLASS_DECLARATION(RigidBody);

		RigidBody(GameObject* owner, rp3d::BodyType type = rp3d::BodyType::DYNAMIC);
		~RigidBody();

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		const rp3d::Transform& GetCurrentTransform() { return m_rigidBody->getTransform(); }
		rp3d::RigidBody* GetRigidBody() { return m_rigidBody; }

		/*
			Manually updates the RigidBody's Transform.  This should only be used for objects with body type STATIC.
		*/
		void UpdateTransformPosition(glm::vec3 pos);
		/*
			Applies force to a RigidBody. This should be used to moved objects with body type DYNAMIC since they are simulated by the physics engine.
		*/
		void ApplyForce(rp3d::Vector3 force);
		/*
			Stops applying force to a RigidBody.
		*/
		void ResetForce();

	private:
		rp3d::RigidBody* m_rigidBody;
		rp3d::Transform m_previousTransform;
	};
}

#endif
