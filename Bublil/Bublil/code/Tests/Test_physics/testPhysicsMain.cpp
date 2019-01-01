#include "testPhysicsAppStateImp.h"
#include<ctime>
/*
Physics
*/
int main_testPhysics()
{
	TestPhysicsApp *PhysicsTest = new TestPhysicsApp(nullptr);

	AppState *PhysicsTestState_result = new TestPhysicsAppState_Result(PhysicsTest, nullptr);
	AppState *PhysicsTestState_input = new TestPhysicsAppState_Input(PhysicsTest, &PhysicsTestState_result);

	PhysicsTest->SetFirst(PhysicsTestState_input);

	Application* testPhysicsApp = PhysicsTest;
	testPhysicsApp->Start();

	//Found another bug in 'restart' !.!
	while (true)
	{
		testPhysicsApp->ReStart();
	}

	return 0;
}