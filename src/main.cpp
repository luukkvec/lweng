#include "engine/engine.h"
#ifdef main
#undef main
#endif
#include <iostream>

int main()
{
	lweng::Engine engine;

	if (!engine.init())
		return -1;
	engine.run();
	engine.close();

	return 0;
}

