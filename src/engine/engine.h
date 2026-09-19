#pragma once

#include "window.h"

namespace lweng
{
	class Engine 
	{
	public:
		Engine();
		~Engine();

		bool init();
		void run();
		void close();

	private:
		bool m_running;
		Window m_window;
	};
}