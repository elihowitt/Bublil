#pragma once

class Application;

class AppState
{
public:
	AppState(Application* machine, AppState* next = nullptr);
	virtual ~AppState();

	AppState* next;
	Application* machine;
	
	virtual void Draw()const = 0;
	virtual void Update() = 0;
protected:
	virtual bool IsDone() = 0;
};

