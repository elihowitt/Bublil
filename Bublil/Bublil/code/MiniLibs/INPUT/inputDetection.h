#pragma once

#include<SDL2\SDL.h>
#undef main

class Application;

namespace input
{
	enum MOUSEBUTTON
	{
		MSB_LEFT = 1,
		MSB_MIDDLE = 2,
		MSB_RIGHT = 3
	};
	enum MOUSEWHEELEVENT
	{
		MSW_UP = 1,
		MSW_DOWN = 2,
		MSW_NOTHING = 0
	};
	struct structMouseState
	{
		Uint32 state;	//Can be checked with SDL_BUTTON.
		int x, y;		//Relative to window.
		//MOUSEWHEELEVENT wheel;
	};

	static SDL_Event inputEvent;
	
	class InputDetector
	{
	public:

		InputDetector() {}
		~InputDetector() {}
	private:

	 const Uint8* keyboardStates;
	 structMouseState mouseState;
	 MOUSEWHEELEVENT mouseWheelState;
	public:
		void update();

		bool KeyDown(SDL_Scancode key)const;
		bool ButtonClicked(input::MOUSEBUTTON button)const;
		
		int getMouseX()const;
		int getMouseY()const;
		input::MOUSEWHEELEVENT getMouseWheelState()const;
	};













	//static bool quit = false;

	//void update();
	////MOUSEWHEELEVENT update();
	//void cleanUp();

	//bool KeyPressed(SDL_Scancode key);
	//bool KeyClicked(MOUSEBUTTON button);
}