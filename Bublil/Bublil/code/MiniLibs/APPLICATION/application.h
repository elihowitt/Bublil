#pragma once

#include<vector>

#include"appState.h"
#include"../code/Globals.h"
#include"INPUT\inputDetection.h"

//enum STATE_FLAGS
//{
//	STATE_QUITE = -1,
//	STATE_REPEAT = -2
//};

class Application
{
public:
	Application(AppState* states) :
		currentState(states), first(states)
	{
		initVals();
	}
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

	virtual void initVals() {}
	
public:

	input::InputDetector inDetec;
	//Idea is to loop calling 
	//	state->Update()
	//	state->Draw()
	//And check if state->IsDone()
	virtual void Start()
	{
		int nextState;
		while (currentState != nullptr)
		{
			currentState->Draw();
			currentState->Update();
			nextState = currentState->IsDone();
			switch (nextState)
			{
			case STATE_FLAGS::STATE_QUITE:
				currentState = nullptr;
				break;
			case STATE_FLAGS::STATE_REPEAT:
				break;
			default:
				currentState = currentState->next[nextState];
				break;
			}
		}
	}

	void ReStart()
	{
		currentState = first;
		initVals();
		Start();
	}
	void SetFirst(AppState* states)/*Also changes current*/ { first = states, currentState = states; }
	
};
