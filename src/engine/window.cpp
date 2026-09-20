#include "window.h"
#include <iostream>

namespace lweng
{
    Window::Window()
        : m_window(nullptr),
        m_context(nullptr),
        m_open(false)
    {
    }

    Window::~Window()
    {
        destroy();
    }

    bool Window::create(const char* title, int w, int h)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE
        );

        m_window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            w,
            h,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );

        if (!m_window)
        {
            std::cout << "failed to create window! "
                << SDL_GetError()
                << "\n";

            return false;
        }

        m_context = SDL_GL_CreateContext(m_window);

        if (!m_context)
        {
            std::cout << "failed to create OpenGL context! "
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
        if (m_context)
        {
            SDL_GL_DeleteContext(m_context);
            m_context = nullptr;
        }

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