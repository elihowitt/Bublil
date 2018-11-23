#include "logger.h"
#include"application.h"

class Test : public Application
{
public:
	Test(AppState* states):Application(states)
	{
		
	}
	~Test() {}

	void Start()override
	{
		while (currentState->next!=nullptr)//Loops all but last state.
		{
			currentState->Draw();
			currentState->Update();
			if (currentState->IsDone())
				currentState = currentState->next;
		}
		while (!currentState->IsDone())
		{
			currentState->Draw();
			currentState->Update();
		}
	}
};

class StateOne : public AppState
{
public:
	StateOne(AppState* next = nullptr, Application* machine = nullptr) :
		AppState(next, machine), pressed(false){}
	StateOne() {}
private:
	bool pressed;
public:
	void Draw()const override
	{
		Sleep(250);
		lg::clear();
		lg::log("Hit that SPACE_BAR key to proceeeeed");
	}
	void Update()override
	{
		if (GetAsyncKeyState(VK_SPACE))
			pressed = true;
	}
	bool IsDone()override
	{
		return pressed;
	}
};
class StateTwo : public AppState
{
public:
	StateTwo(AppState* next = nullptr, Application* machine = nullptr) :
		AppState(next, machine), num(2) {}
	StateTwo() {}
private:
	int num;
public:
	void Draw()const override
	{
		Sleep(250);
		lg::clear();
		lg::log("Give meh multiple of 3!!!!");
	}
	void Update()override
	{
			std::cin >> num;
	}
	bool IsDone()override
	{
		return (num % 3) == 0;
	}
};
class StateThree : public AppState
{
public:
	StateThree(AppState* next = nullptr, Application* machine = nullptr) :
		AppState(next, machine), myNum(rand()%10 + 1),guess(0) {}
	StateThree() {}
private:
	int myNum,guess;
public:
	void Draw()const override
	{
		Sleep(250);
		lg::clear();
		lg::log("Guess a number from - 1 to - 10 :");
	}
	void Update()override
	{
			std::cin >> guess;
	}
	bool IsDone()override
	{
		return myNum == guess;
	}
};


int main()
{
	lg::sayHello();
	lg::log("LOG- Bob`n!!");
	lg::err("ERR- Bob`n!!");
	lg::warn("WARN- Bob`n!!");

	AppState* stateThree = new StateThree(nullptr, nullptr);
	AppState* stateTwo = new StateTwo(stateThree, nullptr);
	AppState* stateOne = new StateOne(stateTwo, nullptr);

	Application* testing = new Test(stateOne);
	testing->Start();

	while (1);
	return 31;
}