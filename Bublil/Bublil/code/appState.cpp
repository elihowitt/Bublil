#include "appState.h"



AppState::AppState(Application* machine_p, AppState* next_p ):
	machine(machine),next(next_p){}

AppState::~AppState()
{
	if (next != nullptr)
		next = nullptr;
	delete next;

	if (machine != nullptr)
		machine = nullptr;
	delete machine;
}
