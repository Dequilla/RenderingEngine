#include "shader.hpp"

#ifdef __opengl__
#include "platform/opengl/glshader.hpp"
#endif

namespace rg
{

    std::unique_ptr<Shader> Shader::create()
    {
#ifdef __opengl__
        return std::make_unique<rg::opengl::GLShader>();
#endif
    }


    std::unique_ptr<ShaderProgram> ShaderProgram::create()
    {
#ifdef __opengl__
    return std::make_unique<rg::opengl::GLShaderProgram>();
#endif
    }
}
