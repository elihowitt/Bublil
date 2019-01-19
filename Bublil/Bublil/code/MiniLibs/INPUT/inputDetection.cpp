#include"inputDetection.h"








//#include<iostream>
//
//void input::update()
//{
//	//MOUSEWHEELEVENT mswe = MSW_NOTHING;
//	//bool noth = false;
//	//if (!SDL_PollEvent(&event))
//	//	//if (SDL_PollEvent(&event))
//	//{
//	//	noth = true;
//	//	//if (event.type == SDL_QUIT)
//	//	//	quit = true;
//	//
//	//	//if (event.type == SDL_MOUSEWHEEL)
//	//		//if (event.wheel.y == 1)
//	//		//	*mouseState.wheel = MSW_DOWN;
//	//		//else
//	//		//	*mouseState.wheel = MSW_UP;
//	//
//	//}
//	////else
//	//	//mouseState.wheel = MSW_NOTHING;
//	while (SDL_PollEvent(&event))
//	{
//		if (event.type == SDL_MOUSEWHEEL)
//		{
//			if (event.wheel.y > 0)
//				mousWheelState = MSW_UP;
//			
//			else //if(event.wheel.y < 0) 
//				mousWheelState = MSW_DOWN;
//		}
//	}
//
//	keyboardStates = SDL_GetKeyboardState(NULL);
//	mouseState.state = SDL_GetMouseState(mouseState.x, mouseState.y);
//}
//
//void input::cleanUp()
//{
//
//}
//
//bool input::KeyPressed(SDL_Scancode key)
//{
//	return keyboardStates[key];
//}
//
//bool input::KeyClicked(MOUSEBUTTON button)
//{
//	return mouseState.state & SDL_BUTTON(button);
//}
//

void input::InputDetector::update()
{
	mouseWheelState = MSW_NOTHING;
	while (SDL_PollEvent(&input::inputEvent))
	{
		if (inputEvent.type == SDL_MOUSEWHEEL)
		{
			if (inputEvent.wheel.y > 0)
				mouseWheelState = MSW_UP;
			
			else //if(inputEvent.wheel.y < 0) 
				mouseWheelState = MSW_DOWN;
		}
	}


	keyboardStates = SDL_GetKeyboardState(NULL);
	mouseState.state = SDL_GetMouseState(&mouseState.x, &mouseState.y);
}

bool input::InputDetector::KeyDown(SDL_Scancode key) const
{
	return keyboardStates[key];
}

bool input::InputDetector::ButtonClicked(input::MOUSEBUTTON button) const
{
	return mouseState.state & SDL_BUTTON(button);
}

int input::InputDetector::getMouseX() const
{
	return mouseState.x;
}

int input::InputDetector::getMouseY() const
{
	return mouseState.y;
}

input::MOUSEWHEELEVENT input::InputDetector::getMouseWheelState() const
{
	return mouseWheelState;
}
