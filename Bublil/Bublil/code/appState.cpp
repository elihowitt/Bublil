#include "appState.h"



AppState::AppState(AppState** next_p):
	next(next_p){}

AppState::~AppState()
{
	if (next != nullptr)
		next = nullptr;
	delete next;
}
