#pragma once

#include "appState.h"
#include"testApp.h"

class TestAppState :public AppState
{
public:
	TestAppState( TestApp* machine_p, AppState* next_p = nullptr) :
		AppState(next_p), machine(machine_p) {}
protected:
	TestApp* machine;
};

