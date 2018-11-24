#pragma once

#include"testAppState.h"
#include"logger.h"
#include<Windows.h>//For none-stopping input.

class TestAppState_Greet : public TestAppState
{
public:
	TestAppState_Greet(TestApp* machine_p, AppState* next_p = nullptr) :
		TestAppState(machine_p, next_p) {}
	void Draw()const override
	{
		lg::log("Hello " + machine->name + " !!");
		lg::log("Press space-bar to proceed...");
		Sleep(250);
		lg::clear();
	}
	void Update()override
	{
		if (GetAsyncKeyState(VK_SPACE))
			machine->wasGreeted = true;
	}
	bool IsDone()const override
	{
		return machine->wasGreeted;
	}
};

class TestAppState_FaveNum : public TestAppState
{
public:
	TestAppState_FaveNum(TestApp* machine_p, AppState* next_p = nullptr) :
		TestAppState(machine_p, next_p) {}
	void Draw()const override
	{
		if (machine->faveNum == -1)//Yet to pick.
			lg::log("Whats your favorite number from 1 to 10 ?");
		else if (machine->faveNum > 10 || machine->faveNum < 1)
		{
			lg::err("Thats not in the range specified!!");
			lg::log("try again!");
			lg::log("Whats your favorite number from 1 to 10 ?");
		}
	}
	void Update()override
	{
		std::cin >> machine->faveNum;
	}
	bool IsDone()const override
	{
		return machine->faveNum >= 1 && machine->faveNum <= 10;
	}
};

class TestAppState_Cube : public TestAppState
{
public:
	TestAppState_Cube(TestApp* machine_p, AppState* next_p = nullptr) :
		TestAppState(machine_p, next_p) {}
	void Draw()const override
	{
		lg::warn("Did you know the cube of " + std::to_string(machine->faveNum) + " is " +
		std::to_string(machine->faveNum*machine->faveNum*machine->faveNum));
		lg::log("Press left-arrow for yes and left for no");
		Sleep(250);
		lg::clear();
	}
	void Update()override
	{
		if (GetAsyncKeyState(VK_LEFT))
			machine->knowsAboutCube = true;
		if (GetAsyncKeyState(VK_RIGHT))
			machine->knowsAboutCube = false;
	}
	bool IsDone()const override
	{
		return machine->knowsAboutCube;
	}
};
