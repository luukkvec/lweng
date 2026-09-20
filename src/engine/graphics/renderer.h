#pragma once

#include <SDL.h>
#include <glad/gl.h>

#include "shader.h"
#include "engine/game/camera.h"

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
        void present(const Camera& camera);

    private:
        SDL_Window* m_window;
        Shader m_shader;

        GLuint m_vao;
        GLuint m_vbo;
    };
}