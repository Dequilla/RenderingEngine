#include "renderer.hpp"

#ifdef __opengl__
#include "platform/opengl/glrenderer3d.hpp"
#endif

namespace rg
{
    std::unique_ptr<Renderer3D> Renderer3D::create()
    {
#ifdef __opengl__
        return std::make_unique<rg::opengl::GLRenderer3D>();
#endif
    }

}
