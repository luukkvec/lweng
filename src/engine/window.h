#pragma once

#include <SDL2/SDL.h>

namespace lweng
{
	class Window
	{
	public:
		Window();
		~Window();

		bool create(const char* title, int w, int h);
		void destroy();

		void process_events();

		bool is_open() const;

		SDL_Window* getWindow() const;
	private:
		SDL_Window* m_window;
		SDL_GLContext m_context;
		bool m_open;
	};
}