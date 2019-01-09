#include "appState.h"



AppState::AppState(AppState** next_p, const int& numNexts_p):
	next(next_p),numNexts(numNexts_p){}

AppState::~AppState()
{
	//if (next != nullptr)
	//	next = nullptr;
	//delete next;
	for (int i = 0; i < numNexts; ++i)
	{
		if (next[i] != nullptr)
			next[i] = nullptr;
		delete[] next[i];
	}
	next = nullptr;
	delete[] next;
}
