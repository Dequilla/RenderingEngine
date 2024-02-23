#include "platform/opengl/gl_shader.hpp"

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

        m_id = gl::glCreateShader(shader_type_to_glenum(shaderType));
        if(m_id == 0)
        {
            std::cout << "Could not create GL shader: " << source << std::endl;
            return false;
        }
        
        const char* cstr = sourceCode.c_str();
        gl::glShaderSource(m_id, 1, &cstr, NULL);
        gl::glCompileShader(m_id);

        int success = 0;
        gl::glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            std::string infoLog(512, '\0');
            gl::glGetShaderInfoLog(m_id, 512, NULL, infoLog.data());
            this->unload();
            std::cout << "Shader compilation failed: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    void GLShader::unload()
    {
        gl::glDeleteShader(m_id);
        m_id = 0;
    }

    GLShaderProgram::GLShaderProgram()
    {
        m_id = gl::glCreateProgram();
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

        gl::glAttachShader(m_id, glshader.m_id);
    }

    bool GLShaderProgram::finish()
    {
        gl::glLinkProgram(m_id);

        int success = 0;
        gl::glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            std::string infoLog(512, '\0');
            gl::glGetProgramInfoLog(m_id, 512, NULL, infoLog.data());
            std::cout << "Unable to link shader program: " << infoLog << std::endl;
            return false;
        }

        return true;
    }

    void GLShaderProgram::unload()
    {
        gl::glDeleteProgram(m_id);
    }

    void GLShaderProgram::use() const
    {
        gl::glUseProgram(m_id);
    }

    void GLShaderProgram::setMat4(const std::string& name, const glm::mat4& matrix) const
    {
        gl::glUniformMatrix4fv(
            gl::glGetUniformLocation(
                m_id, 
                name.c_str()
            ), 
            1, 
            GL_FALSE,
            &matrix[0][0]
        );
    }

 

}

#endif // __opengl__
