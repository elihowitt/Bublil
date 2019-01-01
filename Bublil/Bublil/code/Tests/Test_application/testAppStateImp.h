#pragma once

#include"testAppState.h"
#include"../../loggerMessages.h"
#include"../../loggerTextmanip.h"
#include<Windows.h>//For none-stopping input.

class TestAppState_Greet : public TestAppState
{
public:
	TestAppState_Greet(TestApp* machine_p, AppState** next_p = nullptr) :
		TestAppState(machine_p, next_p) {}
	void Draw()const override
	{
		lg::cwout::generalLog("GREET", "Hello " + machine->name + " !!");
		lg::cwout::generalLog("MESSAGE", "Press space-bar to proceed...");
		Sleep(250);
		lg::cwout::clear();
	}
	void Update()override
	{
		if (GetAsyncKeyState(VK_SPACE))
			machine->wasGreeted = true;
	}
	int IsDone()const override
	{
		if (machine->wasGreeted)
			return 0;


		return STATE_FLAGS::STATE_REPEAT;
	}
};

class TestAppState_FaveNum : public TestAppState
{
public:
	TestAppState_FaveNum(TestApp* machine_p, AppState** next_p = nullptr) :
		TestAppState(machine_p, next_p) {}
	void Draw()const override
	{
		if (machine->faveNum == -1)//Yet to pick.
			lg::cwout::generalLog("QUESTION", "Whats your favorite number from 1 to 10 ?");
		else if (machine->faveNum > 10 || machine->faveNum < 1)
		{
			lg::cwout::err("Thats not in the range specified!!");
			lg::cwout::generalLog("PROMPT", "try again!");
			lg::cwout::generalLog("QUESTION", "Whats your favorite number from 1 to 10 ?");
		}
	}
	void Update()override
	{
		std::cin >> machine->faveNum;
	}
	int IsDone()const override
	{
		if (machine->faveNum >= 1 && machine->faveNum <= 10)
			return 0;


		return STATE_FLAGS::STATE_REPEAT;
	}
};

class TestAppState_Cube : public TestAppState
{
public:
	TestAppState_Cube(TestApp* machine_p, AppState** next_p = nullptr) :
		TestAppState(machine_p, next_p) {}
	void Draw()const override
	{
		lg::cwout::warn("Did you know the cube of " + std::to_string(machine->faveNum) + " is " +
			std::to_string(machine->faveNum*machine->faveNum*machine->faveNum));
		lg::cwout::generalLog("PROMPT", "Press left-arrow for yes and left for no");
		Sleep(250);
		lg::cwout::clear();
	}
	void Update()override
	{
		if (GetAsyncKeyState(VK_LEFT))
			machine->knowsAboutCube = true;
		if (GetAsyncKeyState(VK_RIGHT))
			machine->knowsAboutCube = false;
	}
	int IsDone()const override
	{
		if (machine->knowsAboutCube)
			return STATE_FLAGS::STATE_QUITE;


		return STATE_FLAGS::STATE_REPEAT;
	}
};