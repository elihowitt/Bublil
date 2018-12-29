#pragma once

#include"testPhysicsAppState.h"
#include"../loggerMessages.h"
#include"../loggerTextmanip.h"
#include<Windows.h>//For none-stopping input.

class TestPhysicsAppState_Input : public TestPhysicsAppState
{
public:
	TestPhysicsAppState_Input(TestPhysicsApp* machine_p, AppState** next_p = nullptr) :
		TestPhysicsAppState(machine_p, next_p) {}
	void Draw()const override
	{
		if(machine->centreB == VECTOR_ZERO)
			lg::cwout::generalLog("INPUT", "Enter centre of second sphere:");
		else if(machine->radA == 0)
			lg::cwout::generalLog("INPUT", "Enter radius of first sphere:");
		else
			lg::cwout::generalLog("INPUT", "Enter radius of second sphere:");
	}
	void Update()override
	{
		float in1, in2, in3;
		std::cin >> in1;
		if (machine->centreB == VECTOR_ZERO)
		{
			std::cin >> in2;
			std::cin >> in3;
			machine->centreB = glm::vec3(in1, in2, in3);
		}
		else if (machine->radA == 0)
			machine->radA = in1;
		else
			machine->radB = in1;
	}
	int IsDone()const override
	{		
		if (machine->centreB != VECTOR_ZERO && machine->radA != 0 && machine->radB != 0)
		{
			machine->bodyB.centre = &machine->centreB;
			machine->bodyA.radius = &machine->radA;
			machine->bodyB.radius = &machine->radB;

			machine->doCollide = phy::col::doCollideSimple(machine->bodyA, machine->bodyB);

			return 0;
		}
			
		return STATE_FLAGS::STATE_REPEAT;
	}
};

class TestPhysicsAppState_Result : public TestPhysicsAppState
{
public:
	TestPhysicsAppState_Result(TestPhysicsApp* machine_p, AppState** next_p = nullptr) :
		TestPhysicsAppState(machine_p, next_p) {}
	void Draw()const override
	{
		lg::cwout::basicLog("Sphere A:");
		lg::cwout::basicLog("	centre: "+std::to_string(((int)(*machine->bodyA.centre).x))+
							',' + std::to_string(((int)(*machine->bodyA.centre).y)) + ',' +
								std::to_string(((int)(*machine->bodyA.centre).z)));
		lg::cwout::basicLog("	radius: "+std::to_string((int)(*machine->bodyA.radius))+'\n');

		lg::cwout::basicLog("Sphere B:");
		lg::cwout::basicLog("	centre: " + std::to_string(((int)(*machine->bodyB.centre).x)) +
			',' + std::to_string(((int)(*machine->bodyB.centre).y)) + ',' +
			std::to_string(((int)(*machine->bodyB.centre).z)));
		lg::cwout::basicLog("	radius: " + std::to_string((int)(*machine->bodyB.radius)) + '\n');

		lg::cwout::basicLog("Sum of radii: " + std::to_string(*machine->bodyA.radius + *machine->bodyB.radius));
		lg::cwout::basicLog("Distance: " + std::to_string(distance(*machine->bodyA.centre, *machine->bodyB.centre)));

		if (machine->doCollide)
			lg::cwout::generalLog("RESULT", "They do collide!!");
		else
			lg::cwout::generalLog("RESULT", "They do not collide!!");

		lg::cwout::generalLog("EXIT", "Press space-bar to exit.");

		Sleep(250);
		lg::cwout::clear();
	}
	void Update()override
	{
		if (GetAsyncKeyState(VK_SPACE))
			machine->exitApp = true;
	}
	int IsDone()const override
	{
		if (machine->exitApp)
			return STATE_FLAGS::STATE_QUITE;

		return STATE_FLAGS::STATE_REPEAT;
	}
};