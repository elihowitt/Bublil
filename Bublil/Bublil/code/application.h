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
	virtual void Start()
	{
		///It might be dumb to divide into 2 loops.
		while (currentState != nullptr)//Loops all but last state.
		{
			currentState->Draw();
			currentState->Update();
			int nextState = currentState->IsDone();
			if (nextState != -1)
				currentState = currentState->next[nextState];
		}
	}
	
};
