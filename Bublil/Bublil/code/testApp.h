#pragma once

#include"application.h"
#include"string"

class TestApp :	public Application
{
public:
	TestApp(AppState* states, const std::string& name) :
		Application(states), name(name) 
	{
		wasGreeted = false;	faveNum = -1; knowsAboutCube = false;
	}
	
public:
	std::string name;

	bool wasGreeted;
	int faveNum;
	bool knowsAboutCube;
};

