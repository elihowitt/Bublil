#include "appState.h"



AppState::AppState(AppState* next_p, Application* machine_p ):
	machine(machine_p),next(next_p){}

AppState::~AppState()
{
	if (next != nullptr)
		next = nullptr;
	delete next;

	if (machine != nullptr)
		machine = nullptr;
	delete machine;
}
