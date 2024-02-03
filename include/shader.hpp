#pragma once
#include <vector>
#include <filesystem>

namespace rg
{

    class ShaderImpl;

    class Shader
    {
        friend class ShaderProgram;

        ShaderImpl* m_impl;

    public:
        enum class Type
        {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
            COMPUTE
        };

        Shader();
        Shader(const Shader& other);
        Shader(Shader&& other);
        ~Shader();

        bool load(Shader::Type shaderType, const std::filesystem::path& source);
        void unload();
    };

    class ShaderProgramImpl;

    class ShaderProgram
    {
        ShaderProgramImpl* m_impl;

        std::vector<Shader> m_shaders;

    public:
        ShaderProgram();
        ShaderProgram(const ShaderProgram& other);
        ShaderProgram(ShaderProgram&& other);
        ~ShaderProgram();

        void attach(Shader shader);
        bool finish();
        void unload();

        void use();
    };



}
