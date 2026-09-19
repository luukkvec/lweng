#include <SDL.h>

namespace lweng
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool create(SDL_Window* window);
		void destroy();

		void clear();
		void present();

	private:
		SDL_Renderer* m_renderer;
	};
}