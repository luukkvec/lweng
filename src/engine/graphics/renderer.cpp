#include "renderer.h"
#include <glad/gl.h>
#include <iostream>

namespace lweng
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		destroy();
	}

    bool Renderer::create(SDL_Window* window)
    {
        m_window = window;

        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

        if (version == 0)
        {
            std::cout << "failed to initialize GLAD!\n";
            m_window = nullptr;
            return false;
        }

        std::cout << "OpenGL "
            << GLAD_VERSION_MAJOR(version)
            << "."
            << GLAD_VERSION_MINOR(version)
            << "\n";

        std::cout << "renderer "
            << glGetString(GL_RENDERER)
            << "\n";

        return true;
    }

    void Renderer::destroy()
    {
        m_window = nullptr;
    }

    void Renderer::clear()
    {
        glClearColor(
            0.1f,
            0.1f,
            0.15f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::present()
    {
        SDL_GL_SwapWindow(m_window);
    }
}