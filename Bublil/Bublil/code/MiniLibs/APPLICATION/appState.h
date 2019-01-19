#pragma once

class Application;

class AppState
{

public:
	AppState(AppState** next_p = nullptr, const int& numNexts_p = 1);
	
	virtual ~AppState();

	AppState** next;
	int numNexts;

		///You must give child a machine* to update its variables.

	virtual void Draw()const = 0;//Draws to screen.
	virtual void Update() = 0;//Updates machines vars.
	virtual int IsDone()const = 0;//acoording to info returns if
								   //to progress to next state.
								   // -1 means false, otherwise result represents index of nex state.

};

