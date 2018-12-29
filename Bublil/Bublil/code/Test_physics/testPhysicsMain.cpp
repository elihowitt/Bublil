#include "testPhysicsAppStateImp.h"
#include<ctime>
/*
Physics
*/
int main()
{
	TestPhysicsApp *test = new TestPhysicsApp(nullptr);

	AppState *testState_result = new TestPhysicsAppState_Result(test, nullptr);
	AppState *testState_input = new TestPhysicsAppState_Input(test, &testState_result);

	test->SetFirst(testState_input);

	Application* testApp = test;
	testApp->Start();

	srand(time(0));
	while (1)
	{
		Sleep(600);
		lg::cwout::sayHello();
	}

	return 0;
}