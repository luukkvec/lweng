#pragma once

#include "window.h"
#include "graphics/renderer.h"
#include "game/camera.h"

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
		Renderer m_renderer;
		Camera m_camera;
	};
}