#include "engine.h"
#include <iostream>

int main()
{
    lweng::Engine engine;

    if (!engine.init())
    {
        std::cout << "engine failed to initialize!\n";
        return -1;
    }
    engine.run();
    engine.close();

    return 0;
}

