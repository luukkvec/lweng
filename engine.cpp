#include "engine.h"
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

        m_running = true;

        return true;
    }

    void Engine::run()
    {
        string input;

        while (m_running)
        {
            std::cout << "running\n";

            getline(cin, input);

            if (!input.empty())
            {
                m_running = false;
            }
        }
    }

    void Engine::close()
    {
        std::cout << "closing\n";

        m_running = false;
    }
}