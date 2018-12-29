#include "testAppStateImp.h"
#include<ctime>

int main_()
{
	TestApp *test = new TestApp(nullptr, "Bob`n");

	AppState *testState_cube = new TestAppState_Cube(test, nullptr);
	AppState *testState_faveNum = new TestAppState_FaveNum(test, &testState_cube);
	AppState *testState_greet = new TestAppState_Greet(test, &testState_faveNum);

	test->SetFirst(testState_greet);

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