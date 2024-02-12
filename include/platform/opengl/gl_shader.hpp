#pragma once
#include <vector>
#include <filesystem>

#include "shader.hpp"

#ifdef __opengl__
#include "platform/opengl/opengl.hpp"

namespace rg::opengl
{

    class GLShaderProgram;

    class GLShader : public Shader
    {
        friend class rg::opengl::GLShaderProgram;

        GLuint m_id;

    public:
        GLShader();
        GLShader(const GLShader& other);
        GLShader(GLShader&& other);
        ~GLShader();

        virtual bool load(Shader::Type shaderType, const std::filesystem::path& source) override;
        virtual void unload() override;
    };

    class GLShaderProgram : public ShaderProgram
    {
        GLuint m_id;        

    public:
        GLShaderProgram();
        GLShaderProgram(const GLShaderProgram& other);
        GLShaderProgram(GLShaderProgram&& other);
        ~GLShaderProgram();

        virtual void attach(const Shader& shader) override;
        virtual bool finish() override;
        virtual void unload() override;

        virtual void use() const override;

        virtual void setMat4(const std::string& name, const glm::mat4& matrix) const override;
    };

}

#endif // __opengl__
