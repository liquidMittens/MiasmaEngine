#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_
#include "Collider.h"
#include "reactphysics3d/reactphysics3d.h"
#include "reactphysics3d/collision/Collider.h"
#include "glm/glm.hpp"

namespace Miasma::RTTI
{
	class BoxCollider : public Collider
	{
	public:
		CLASS_DECLARATION(BoxCollider);

		BoxCollider(GameObject* owner, glm::vec3 halfExtents);
		~BoxCollider();

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		rp3d::Collider* GetCollider() { return m_collider; }

	private:
		rp3d::BoxShape* m_boxShape;
		rp3d::Collider* m_collider;
	};
}

#endif
