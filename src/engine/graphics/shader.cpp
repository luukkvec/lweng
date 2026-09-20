#include "shader.h"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

// this took way too long
namespace lweng
{
    Shader::Shader() : m_program(0)
    {        
    }

    Shader::~Shader() 
    {
        destroy();
    }

    bool Shader::create(const char* vertex_source, const char* fragment_source)
    {
                GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(
            vertex_shader,
            1,
            &vertex_source,
            nullptr
        );

        glCompileShader(vertex_shader);

        GLint success = 0;

        glGetShaderiv(
            vertex_shader,
            GL_COMPILE_STATUS,
            &success
        );

        if (!success)
        {
            char log[512];

            glGetShaderInfoLog(
                vertex_shader,
                sizeof(log),
                nullptr,
                log
            );

            std::cout
                << "vertex shader compilation failed!\n"
                << log
                << "\n";

            glDeleteShader(vertex_shader);

            return false;
        }

        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(
            fragment_shader,
            1,
            &fragment_source,
            nullptr
        );

        glCompileShader(fragment_shader);

        glGetShaderiv(
            fragment_shader,
            GL_COMPILE_STATUS,
            &success
        );

        if (!success)
        {
            char log[512];

            glGetShaderInfoLog(
                fragment_shader,
                sizeof(log),
                nullptr,
                log
            );

            std::cout
                << "fragment shader compilation failed!\n"
                << log
                << "\n";

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            return false;
        }

        m_program = glCreateProgram();

        glAttachShader(m_program, vertex_shader);
        glAttachShader(m_program, fragment_shader);

        glLinkProgram(m_program);

        glGetProgramiv(
            m_program,
            GL_LINK_STATUS,
            &success
        );

        if (!success)
        {
            char log[512];

            glGetProgramInfoLog(
                m_program,
                sizeof(log),
                nullptr,
                log
            );

            std::cout
                << "shader program linking failed!\n"
                << log
                << "\n";

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            glDeleteProgram(m_program);
            m_program = 0;

            return false;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return true;
    }

    void Shader::destroy()
    {
        if (m_program != 0)
        {
            glDeleteProgram(m_program);
            m_program = 0;
        }
    }

        void Shader::bind() const
    {
        glUseProgram(m_program);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    GLuint Shader::get_program() const
    {
        return m_program;
    }

    GLint Shader::get_uniform_location(const std::string& name) const
    {
        auto it = m_uniform_cache.find(name);
        if (it != m_uniform_cache.end())
        {
            return it->second;
        }

        GLint location = glGetUniformLocation(m_program, name.c_str());

        if (location == -1)
        {
            std::cout << "warning! uniform '" << name << "' not found or unused\n";
        }

        m_uniform_cache[name] = location;
        return location;
    }

    void Shader::set_mat4(const std::string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::set_vec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(value));
    }

    void Shader::set_int(const std::string& name, int value) const
    {
        glUniform1i(get_uniform_location(name), value);
    }

    void Shader::set_float(const std::string& name, float value) const
    {
        glUniform1f(get_uniform_location(name), value);
    }
}