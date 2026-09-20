#include "renderer.h"
#include <glad/gl.h>
#include <iostream>

namespace lweng
{
	Renderer::Renderer() :
    m_window(nullptr),
    m_vao(0),
    m_vbo(0)
	{
	}

    const char* vertex_shader_source = R"(
    #version 330 core

    layout (location = 0) in vec2 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
    )";

    const char* fragment_shader_source = R"(
    #version 330 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0, 0.3, 0.2, 1.0);
    }
    )";

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

        if (!m_shader.create(vertex_shader_source,
            fragment_shader_source))
        {
            return false;
        }

        float vertices[] =
        {
            0.0f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
        };

        // create vbo

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW
        );

        // create vao

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        // make vertex thing do vertex stuff

        glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            2 * sizeof(float),
            (void*)0
        );

        // unbind vertex
   
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);


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

        m_shader.bind();

        std::cout << "Shader created: "
          << m_shader.get_program()
          << "\n";

        glBindVertexArray(m_vao);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );

        glBindVertexArray(0);

        m_shader.unbind();
        
        SDL_GL_SwapWindow(m_window);
    }
}