#include "Physics.hpp"

bool Physics::init = false;

btBroadphaseInterface* Physics::broadphase = NULL;
btDefaultCollisionConfiguration* Physics::collisionConfiguration = NULL;

btSequentialImpulseConstraintSolver* Physics::solver = NULL;

btCollisionDispatcher* Physics::dispatcher = NULL;
btDiscreteDynamicsWorld* Physics::dynamicsWorld = NULL;

void Physics::initialize()
{
	if (init)
		return;

	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	
	solver = new btSequentialImpulseConstraintSolver;

	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	init = true;
}

void Physics::terminate()
{
	if (!init)
		return;

	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;

	init = false;
}
