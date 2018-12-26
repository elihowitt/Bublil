#pragma once

#include "../appState.h"
#include "TestApp.h"

class TestAppState :public AppState
{
public:
	TestAppState(TestApp* machine_p, AppState** next_p = nullptr, const int& numNexts_p = 1) :
		AppState(next_p, numNexts_p), machine(machine_p) {}
protected:
	TestApp * machine;
};