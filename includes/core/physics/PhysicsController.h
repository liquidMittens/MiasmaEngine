#ifndef PHYSICSCONTROLLER_H_
#define PHYSICSCONTROLLER_H_
#include <memory>
#include "reactphysics3d/reactphysics3d.h"
#include "components/CollisionBody.h"
#include "components/RigidBody.h"
#include <vector>
using namespace Miasma::RTTI;

namespace Miasma::Physics
{
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
		long double GetAccumulator() const { return accumulator; }

		/// This method is called when some contacts occur
		virtual void onContact(const CallbackData& callbackData) override;

	private:
		static std::unique_ptr<PhysicsController> m_instance;
		rp3d::PhysicsCommon m_physicsCommon;
		rp3d::PhysicsWorld* m_physicsWorld;
		std::vector<CollisionBody*> m_collisionBodyList;
		std::vector<RigidBody*> m_rigidBodyList;
		long double accumulator;
	};
}

#endif
