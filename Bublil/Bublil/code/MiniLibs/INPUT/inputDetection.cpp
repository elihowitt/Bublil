#include"inputDetection.h"

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
