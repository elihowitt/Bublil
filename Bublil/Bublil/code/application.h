#pragma once

#include"appState.h"
#include"CoreUtils.h"

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
			//if (nextState != -1)
			//	currentState = currentState->next[nextState];
		}
	}

	void ReStart()
	{
		currentState = first;
		Start();
	}
	void SetFirst(AppState* states)/*Also changes current*/ { first = states, currentState = states; }
	
};
