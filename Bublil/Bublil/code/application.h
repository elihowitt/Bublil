#pragma once

#include"appState.h"

class Application
{
public:
	Application(AppState* states) :
		currentState(states), first(states) {}
	virtual ~Application()
	{
		if (currentState != nullptr)
			currentState = nullptr;
		delete currentState;
	}
protected:
	//One state which will change according to events 
	//and one constant state for restarting.
	AppState* currentState, const *first;
public:
	//Idea is to loop calling 
	//	state->Update()
	//	state->Draw()
	//And check if state->IsDone()
	virtual void Start() = 0;
	
};
