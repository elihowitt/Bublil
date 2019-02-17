#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include<SDL2/SDL.h>
#include<string>

namespace render
{
	class Display
	{
	public:
		Display(int width, int height, const std::string& title);

		void Clear(float r, float g, float b, float a);
		void Update();
		bool IsClosed();

		SDL_Window* GetWindow() { return m_window; }

		virtual ~Display();

	protected:
	private:
		Display(const Display& other) {}
		Display& operator=(const Display& other) {}

		SDL_Window* m_window;
		SDL_GLContext m_glContext;
		bool m_isClosed;
	};
}
#endif

