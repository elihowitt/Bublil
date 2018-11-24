#include"testAppStatesImp.h"

int main()
{
	TestApp *test = new TestApp(nullptr, "Bob`n");

	TestAppState_Cube testState_cube(test, nullptr);
	TestAppState_FaveNum testState_faveNum(test, &testState_cube);
	TestAppState_Greet testState_greet(test, &testState_faveNum);

	test->SetFirst(&testState_greet);

	Application* testApp = test;
	testApp->Start();

	return 0;
}