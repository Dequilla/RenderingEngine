#include "renderer.hpp"

#ifdef __opengl__
#include "platform/opengl/gl_renderer3d.hpp"
#define RG_RENDERER_3D_IMPL rg::opengl::GLRenderer3D
#endif

namespace rg
{
    std::unique_ptr<Renderer3D> Renderer3D::create()
    {
        return std::make_unique<RG_RENDERER_3D_IMPL>();
    }

}
