#include<iostream>

#include"INPUT\inputDetection.h"

using namespace input;

#undef main
int main()
//int main_checkInput()
{

	InputDetector inDetec;

	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_SetRelativeMouseMode(SDL_TRUE); //Hides the mouse! dope!.

	SDL_Window* win = SDL_CreateWindow("Bob", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(win
	);

	SDL_CaptureMouse(SDL_TRUE);
	SDL_Event e;

	SDL_MouseWheelEvent mwe;

	//SDL_SetWindowInputFocus(win);

	inDetec.update();
	while (!inDetec.KeyDown(SDL_SCANCODE_ESCAPE))
	{
		inDetec.update();

		switch (inDetec.getMouseWheelState())
		{
			case MSW_DOWN:
				std::cout << "SCROLL DOWN!!\n";
				break;
			case MSW_UP:
				std::cout << "SCROLL UP!!\n";
				break;
			case MSW_NOTHING:
			default:
				break;
		}

		if (inDetec.KeyDown(SDL_SCANCODE_E))
			std::cout << "~~~E~~~";

		if (inDetec.KeyDown(SDL_SCANCODE_P))
			std::cout << '(' << inDetec.getMouseX() << ", " << inDetec.getMouseY() << ")\n";

		if (inDetec.ButtonClicked(MSB_RIGHT))
			std::cout << "Right mouse clicked!!11!\n";

	}

	return 0;
}