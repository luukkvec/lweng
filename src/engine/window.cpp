#include "window.h"
#include <iostream>

namespace lweng
{
	Window::Window()
		: m_window(nullptr),
		m_open(false)
	{
	}

	Window::~Window()
	{
		destroy();
	}

	bool Window::create(const char* title, int w, int h)
	{
		m_window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			w,
			h,
			0
		);

		int actual_w;
		int actual_h;

		SDL_GetWindowSize(m_window, &actual_w, &actual_h);

		std::cout << "Window size: "
			<< actual_w << "x" << actual_h << "\n";

		if (!m_window)
		{
			std::cout << "failed to initialize window! "
				<< SDL_GetError()
				<< "\n";

			destroy();
			return false;
		}

		m_open = true;

		return true;
	}

	void Window::destroy()
	{
		if (m_window)
		{
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}

		m_open = false;
	}

	void Window::process_events()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				m_open = false;
			}
		}
	}

	bool Window::is_open() const
	{
		return m_open;
	}

	SDL_Window* Window::getWindow() const
	{
		return m_window;
	}
}