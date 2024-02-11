#include "model.hpp"

#ifdef __opengl__
#include "platform/opengl/glmodel.hpp"
#endif

namespace rg
{

    std::unique_ptr<Mesh> Mesh::create(const VertexBuffer& vertices, const IndexBuffer& indices)
    {
#ifdef __opengl__
        return std::make_unique<rg::opengl::GLMesh>(vertices, indices);
#endif
    }

}
