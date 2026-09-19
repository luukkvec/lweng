#include "engine.h"
#include <SDL.h>
#include <iostream>
#include <string>

using namespace std;

namespace lweng
{
    Engine::Engine() : m_running(false) {}
    Engine::~Engine() {}

    bool Engine::init()
    {
        std::cout << "initialized\n";

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "failed to initialize SDL! "
                << SDL_GetError()
                << "\n";

            return false;
        }

        std::cout << "SDL version: "
            << SDL_MAJOR_VERSION << "."
            << SDL_MINOR_VERSION << "."
            << SDL_PATCHLEVEL << "\n";

        if (!m_window.create("lweng", 1280, 720))
        {
            SDL_Quit();
            return false;
        }

        m_running = true;

        return true;
    }

    void Engine::run()
    {
        string input;

        while (m_running && m_window.is_open())
        {
            m_window.process_events();
        }
    }

    void Engine::close()
    {
        std::cout << "closing\n";

        m_window.destroy();

        m_running = false;
    }
}