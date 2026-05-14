#ifndef CAPSULECOLLIDER_H_
#define CAPSULECOLLIDER_H_
#include <Miasma/core/ecs/Component.h>
#include <Miasma/core/reactphysics3d/reactphysics3d.h>

namespace Miasma::Component
{
	class CapsuleCollider : public Component
	{
	public:
		CLASS_DECLARATION(CapsuleCollider);

		CapsuleCollider(GameObject* owner, float radius, float height);
		~CapsuleCollider();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		rp3d::Collider* GetCollider() { return m_collider; }

	private:
		rp3d::CapsuleShape* m_capsuleShape;
		rp3d::Collider* m_collider;
	};
}

#endif
