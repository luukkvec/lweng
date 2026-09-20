#include "renderer.h"
#include <iostream>

namespace lweng
{
    Renderer::Renderer()
        : m_renderer(nullptr)
    {
    }

    Renderer::~Renderer()
    {
        destroy();
    }

    bool Renderer::create(SDL_Window* window)
    {
        m_renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
        );

        if (!m_renderer)
        {
            std::cout << "failed to create renderer! "
                      << SDL_GetError()
                      << "\n";

            return false;
        }

        return true;
    }

    void Renderer::destroy()
    {
        if (m_renderer) 
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
    }

    void Renderer::clear()
    {
        SDL_SetRenderDrawColor(
            m_renderer,
            30,
            30,
            30,
            255
        );

        SDL_RenderClear(m_renderer);
    }

    void Renderer::present()
    {
        SDL_RenderPresent(m_renderer);
    }
}