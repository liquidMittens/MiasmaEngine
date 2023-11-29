#ifndef PHYSICSCONTROLLER_H_
#define PHYSICSCONTROLLER_H_
#include <memory>
#include "reactphysics3d/reactphysics3d.h"
#include "components/CollisionBody.h"
#include "components/RigidBody.h"
#include <vector>
#include "box2d.h"
using namespace Miasma::Component;

namespace Miasma::Physics
{
	constexpr int velocityIterations = 6;
	constexpr int positionIterations = 2;

	class PhysicsController : public rp3d::CollisionCallback
	{
	public:
		
		PhysicsController();
		~PhysicsController();

		static PhysicsController& GetInstance()
		{
			if (m_instance == nullptr) {
				m_instance = std::make_unique<PhysicsController>();
			}
			return (*m_instance.get());
		}

		PhysicsController(const PhysicsController&) = delete;
		PhysicsController& operator=(const PhysicsController&) = delete;

		bool InitializePhysicsController();
		void UpdatePhysicsSimulation(float dt);
		void ShutdownPhysicsController();

		void AddBodyToList(CollisionBody* newBody);
		void AddRigidBodyToList(RigidBody* newBody);

		rp3d::PhysicsCommon& GetPhysicsCommon() { return m_physicsCommon; }
		rp3d::PhysicsWorld* GetPhysicsWorld() { return m_physicsWorld; }
		b2World* GetPhysics2DWorld() { return m_physicsWorld2D; }
		long double GetAccumulator() const { return accumulator; }

		/// This method is called when some contacts occur
		virtual void onContact(const CallbackData& callbackData) override;

	private:
		static std::unique_ptr<PhysicsController> m_instance;
		rp3d::PhysicsCommon m_physicsCommon;
		rp3d::PhysicsWorld* m_physicsWorld;
		b2World* m_physicsWorld2D;
		std::vector<CollisionBody*> m_collisionBodyList;
		std::vector<RigidBody*> m_rigidBodyList;
		long double accumulator;
	};
}

#endif
