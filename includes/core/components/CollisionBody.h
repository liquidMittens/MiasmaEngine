#ifndef COLLISIONBODY_H_
#define COLLISIONBODY_H_
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"

namespace Miasma::Component
{

	class CollisionBody : public Component
	{
	public:

		CLASS_DECLARATION(CollisionBody);

		CollisionBody(GameObject* owner);
		~CollisionBody();

		// behavior functions
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Shutdown() override;

		const rp3d::Transform& GetCurrentTransform() { return m_collisionBody->getTransform(); }
		rp3d::CollisionBody* GetCollisionBody() { return m_collisionBody; }

	private:
		rp3d::CollisionBody* m_collisionBody;
	};

}
#endif
