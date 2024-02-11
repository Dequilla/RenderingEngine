#include "platform/opengl/glshader.hpp"

#ifdef __opengl__
#include <stdexcept>
#include <fstream>
#include <iostream>

#include "platform/opengl/opengl.hpp"

namespace rg::opengl
{

    GLShader::GLShader()
    {
    }
    
    GLShader::GLShader(const GLShader& other)
    {
        m_id = other.m_id;
    }

    GLShader::GLShader(GLShader&& other)
    {
        this->m_id = other.m_id;
        other.m_id = 0;
    }

    GLShader::~GLShader()
    {
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


    bool GLShader::load(Shader::Type shaderType, const std::filesystem::path& source)
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

        m_id = gl::createShader(shader_type_to_glenum(shaderType));
        if(m_id == 0)
        {
            std::cout << "Could not create GL shader: " << source << std::endl;
            return false;
        }
        
        const char* cstr = sourceCode.c_str();
        gl::shaderSource(m_id, 1, &cstr, NULL);
        gl::compileShader(m_id);

        int success = 0;
        gl::getShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            std::string infoLog(512, '\0');
            gl::getShaderInfoLog(m_id, 512, NULL, infoLog.data());
            this->unload();
            std::cout << "Shader compilation failed: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    void GLShader::unload()
    {
        gl::deleteShader(m_id);
        m_id = 0;
    }

    GLShaderProgram::GLShaderProgram()
    {
        m_id = gl::createProgram();
    }

    GLShaderProgram::~GLShaderProgram()
    {
    }

    GLShaderProgram::GLShaderProgram(const GLShaderProgram& other)
    {
        m_id = other.m_id;
    }

    GLShaderProgram::GLShaderProgram(GLShaderProgram&& other)
    {
        m_id = other.m_id;
        other.m_id = 0;
    }

    void GLShaderProgram::attach(const Shader& shader)
    {
        const GLShader& glshader = static_cast<const GLShader&>(shader);

        gl::attachShader(m_id, glshader.m_id);
    }

    bool GLShaderProgram::finish()
    {
        gl::linkProgram(m_id);

        int success = 0;
        gl::getProgramiv(m_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            std::string infoLog(512, '\0');
            gl::getProgramInfoLog(m_id, 512, NULL, infoLog.data());
            std::cout << "Unable to link shader program: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    void GLShaderProgram::unload()
    {
        gl::deleteProgram(m_id);
    }

    void GLShaderProgram::use()
    {
        gl::useProgram(m_id);
    }

}

#endif // __opengl__
