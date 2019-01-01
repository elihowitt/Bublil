#pragma once

#include "../../appState.h"
#include "testPhysicsApp.h"

class TestPhysicsAppState :public AppState
{
public:
	TestPhysicsAppState(TestPhysicsApp* machine_p, AppState** next_p = nullptr, const int& numNexts_p = 1) :
		AppState(next_p, numNexts_p), machine(machine_p) {}
protected:
	TestPhysicsApp * machine;
};