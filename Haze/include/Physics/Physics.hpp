#ifndef HAZE_PHYSICS_HPP
#define HAZE_PHYSICS_HPP

#include "btBulletDynamicsCommon.h"

class Physics
{
	static bool init;

	static btBroadphaseInterface* broadphase;
	static btDefaultCollisionConfiguration* collisionConfiguration;

	static btSequentialImpulseConstraintSolver* solver;

	static btCollisionDispatcher* dispatcher;
	static btDiscreteDynamicsWorld* dynamicsWorld;
	Physics();
public:
	static void initialize();
	static void terminate();
};

#endif !HAZE_PHYSICS_HPP
