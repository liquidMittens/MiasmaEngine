#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"

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

		rp3d::Transform& GetCurrentTransform() { return m_transform; }
		rp3d::RigidBody* GetCollider() { return m_rigidBody; }

	private:
		rp3d::RigidBody* m_rigidBody;
		rp3d::Transform m_transform;
	};
}

#endif
