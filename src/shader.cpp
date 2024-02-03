#include "shader.hpp"

#ifdef __opengl__
#include <stdexcept>
#include <fstream>
#include <iostream>

#include "platform/opengl.hpp"

namespace rg
{

    class ShaderImpl
    {
        friend class Shader;
        friend class ShaderProgram;
    
        GLuint m_id;
    };

    Shader::Shader()
    {
        m_impl = new ShaderImpl();
    }
    
    Shader::Shader(const Shader& other)
    {
        m_impl = new ShaderImpl();
        m_impl->m_id = other.m_impl->m_id;
    }

    Shader::Shader(Shader&& other)
    {
        this->m_impl = other.m_impl;
        other.m_impl = nullptr;
    }

    Shader::~Shader()
    {
        if(m_impl != nullptr)
        {
            delete m_impl;
            m_impl = nullptr;
        }
    }

    GLenum shader_type_to_glenum(Shader::Type shaderType)
    {
        switch(shaderType)
        {
            case Shader::Type::VERTEX:
                return GL_VERTEX_SHADER;
            case Shader::Type::FRAGMENT:
                return GL_FRAGMENT_SHADER;
            case Shader::Type::GEOMETRY:
                return GL_GEOMETRY_SHADER;
            case Shader::Type::COMPUTE:
                return GL_COMPUTE_SHADER;
            defualt:
                throw std::runtime_error("Invalid shader type");
        }

        return GL_INVALID_ENUM;
    }


    bool Shader::load(Shader::Type shaderType, const std::filesystem::path& source)
    {
        std::ifstream t(source);

        if(!t.is_open())
        {
            std::cout << "Could not find file: " << source << std::endl;
            return false;
        }

        std::stringstream ss;
        ss << t.rdbuf();
        std::string sourceCode = ss.str();

        if(sourceCode.empty())
        {
            std::cout << "Shader file was empty: " << source << std::endl;
            return false;
        }

        m_impl->m_id = gl::createShader(shader_type_to_glenum(shaderType));
        if(m_impl->m_id == 0)
        {
            std::cout << "Could not create GL shader: " << source << std::endl;
            return false;
        }
        
        const char* cstr = sourceCode.c_str();
        gl::shaderSource(m_impl->m_id, 1, &cstr, NULL);
        gl::compileShader(m_impl->m_id);

        int success = 0;
        gl::getShaderiv(m_impl->m_id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            std::string infoLog(512, '\0');
            gl::getShaderInfoLog(m_impl->m_id, 512, NULL, infoLog.data());
            this->unload();
            std::cout << "Shader compilation failed: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    void Shader::unload()
    {
        gl::deleteShader(m_impl->m_id);
        m_impl->m_id = 0;
    }

    class ShaderProgramImpl
    {
        friend class ShaderProgram;

        GLuint m_id;
    };

    ShaderProgram::ShaderProgram()
    {
        m_impl = new ShaderProgramImpl();
        m_impl->m_id = gl::createProgram();
    }

    ShaderProgram::~ShaderProgram()
    {
        if(m_impl != nullptr)
        {
            delete m_impl;
            m_impl = nullptr;
        }
    }

    ShaderProgram::ShaderProgram(const ShaderProgram& other)
    {
        m_impl = new ShaderProgramImpl();
        m_impl->m_id = other.m_impl->m_id;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& other)
    {
        m_impl = other.m_impl;
        other.m_impl = nullptr;
    }

    void ShaderProgram::attach(Shader shader)
    {
        m_shaders.push_back(shader);
        gl::attachShader(m_impl->m_id, shader.m_impl->m_id);
    }

    bool ShaderProgram::finish()
    {
        gl::linkProgram(m_impl->m_id);

        int success = 0;
        gl::getProgramiv(m_impl->m_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            std::string infoLog(512, '\0');
            gl::getProgramInfoLog(m_impl->m_id, 512, NULL, infoLog.data());
            std::cout << "Unable to link shader program: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    void ShaderProgram::unload()
    {
        gl::deleteProgram(m_impl->m_id);
    }

    void ShaderProgram::use()
    {
        gl::useProgram(m_impl->m_id);
    }

}

#endif // __opengl__
