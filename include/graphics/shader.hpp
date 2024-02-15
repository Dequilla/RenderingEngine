#pragma once

#include <memory>
#include <vector>
#include <filesystem>

#include "glm/glm.hpp"

namespace rg
{

    class Shader
    {
    public:
        enum class Type
        {
            VERTEX,
            FRAGMENT,
            GEOMETRY,
            COMPUTE
        };

        virtual ~Shader() = default;

        virtual bool load(Shader::Type shaderType, const std::filesystem::path& source) = 0;
        virtual void unload() = 0;

        static std::unique_ptr<Shader> create();
    };


    class ShaderProgram
    {
    public:
        virtual ~ShaderProgram() = default;

        virtual void attach(const Shader& shader) = 0;
        virtual bool finish() = 0;
        virtual void unload() = 0;

        virtual void use() const = 0; 

        virtual void setMat4(const std::string& name, const glm::mat4& matrix) const = 0;

        static std::unique_ptr<ShaderProgram> create();
    };

    
}
