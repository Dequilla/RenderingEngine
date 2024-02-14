#include "model.hpp"

#ifdef __opengl__
#include "platform/opengl/gl_model.hpp"
#define RG_MODEL_IMPL rg::opengl::GLMesh
#endif

namespace rg
{

    std::unique_ptr<Mesh> Mesh::create(const VertexBuffer& vertices, const IndexBuffer& indices)
    {
        return std::make_unique<RG_MODEL_IMPL>(vertices, indices);
    }

}
