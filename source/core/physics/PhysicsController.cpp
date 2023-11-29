#include "physics/PhysicsController.h"
using namespace Miasma::Physics;
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

std::unique_ptr<PhysicsController> PhysicsController::m_instance = nullptr;

PhysicsController::PhysicsController() : 
	m_physicsWorld(nullptr),
	m_physicsWorld2D(nullptr),
	accumulator(0)
{
	rp3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 20;
	//settings.isSleepingEnabled = false;
	settings.gravity = rp3d::Vector3(0.0f, -9.81f, 0.0f);
	settings.defaultFrictionCoefficient = 0.75;
	settings.restitutionVelocityThreshold = 0.5;
	m_physicsWorld = m_physicsCommon.createPhysicsWorld(settings);
	assert(m_physicsWorld != nullptr);

	// create 2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	m_physicsWorld2D = new b2World(gravity);
}

PhysicsController::~PhysicsController()
{

}

void PhysicsController::AddBodyToList(CollisionBody* newBody)
{
	if (newBody != nullptr) {
		m_collisionBodyList.push_back(newBody);
	}
}

void PhysicsController::AddRigidBodyToList(RigidBody* newBody)
{
	if (newBody != nullptr) {
		m_rigidBodyList.push_back(newBody);
	}
}

bool PhysicsController::InitializePhysicsController()
{
	bool initsuccess = true;
	return initsuccess;
}

void PhysicsController::UpdatePhysicsSimulation(float dt)
{
	// Constant physics time step
	const float timeStep = 1.0f / 60.0f;
	// Get the current system time
	long double currentFrameTime = glfwGetTime();
	// Compute the time difference between the two frames
	long double deltaTime = dt;
	// Update the previous time
	long double previousFrameTime = currentFrameTime;
	// Add the time difference in the accumulator
	accumulator += deltaTime;
	// While there is enough accumulated time to take
	// one or several physics steps
	while (accumulator >= timeStep) {
		// Update the Dynamics world with a constant time step
		m_physicsWorld->update(timeStep);
		m_physicsWorld2D->Step(timeStep, velocityIterations, positionIterations);
		// Decrease the accumulated time
		accumulator -= timeStep;
	}
}

void PhysicsController::ShutdownPhysicsController()
{
	m_physicsCommon.destroyPhysicsWorld(m_physicsWorld);
}

// This method is called when some contacts occur
void PhysicsController::onContact(const CallbackData& callbackData) {

	// For each contact pair
	for (unsigned int p = 0; p < callbackData.getNbContactPairs(); p++) {

		ContactPair contactPair = callbackData.getContactPair(p);

		// For each contact point of the contact pair
		for (unsigned int c = 0; c < contactPair.getNbContactPoints(); c++) {

			ContactPoint contactPoint = contactPair.getContactPoint(c);

			// Contact normal
			/*rp3d::Vector3 normal = contactPoint.getWorldNormal();
			openglframework::Vector3 contactNormal(normal.x, normal.y, normal.z);

			rp3d::Vector3 point1 = contactPoint.getLocalPointOnCollider1();
			point1 = contactPair.getCollider1()->getLocalToWorldTransform() * point1;

			openglframework::Vector3 position1(point1.x, point1.y, point1.z);
			mContactPoints.push_back(SceneContactPoint(position1, contactNormal, openglframework::Color::red()));

			rp3d::Vector3 point2 = contactPoint.getLocalPointOnCollider2();
			point2 = contactPair.getCollider2()->getLocalToWorldTransform() * point2;
			openglframework::Vector3 position2(point2.x, point2.y, point2.z);
			mContactPoints.push_back(SceneContactPoint(position2, contactNormal, openglframework::Color::blue()));*/
		}
	}
}