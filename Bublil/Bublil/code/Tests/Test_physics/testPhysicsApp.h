#pragma once

#include"../../application.h"
#include"../../physicsNS.h"

class TestPhysicsApp : public Application
{
public:
	TestPhysicsApp(AppState* states) :
		Application(states),bodyA(phy::col::CBT_SPHERE, true, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr),
		bodyB(phy::col::CBT_SPHERE, true, &VECTOR_ZERO, nullptr, nullptr, nullptr, nullptr, nullptr)
	{
		initVals();
		bodyA.centre = &VECTOR_ZERO;
	}
private:
	void initVals()override
	{
		centreB = glm::vec3(0, 0, 0);
		radA = 0;
		radB = 0;
		doCollide = false;
		exitApp = false;
	}
public:
	phy::col::CollisionBody bodyA, bodyB;

	float radA, radB;

	glm::vec3 centreB;

	bool doCollide;

	bool exitApp;
};
