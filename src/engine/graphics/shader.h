#pragma once

#include <glad/gl.h>

namespace lweng
{
    class Shader
    {
    public:
        Shader();
        ~Shader();

        bool create(const char* vertex_source, const char* fragment_source);
        void destroy();

        void bind() const;
        void unbind() const;

        GLuint get_program() const;
    private:
        GLuint m_program;
    };
}