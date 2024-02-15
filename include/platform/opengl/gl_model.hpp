#pragma once
#include <stddef.h>

#ifdef __opengl__

#include "graphics/model.hpp"
#include "platform/opengl/opengl.hpp"

namespace rg::opengl
{
    class GLRenderer3D;
    
    class GLMesh : public rg::Mesh
    {
        friend class rg::opengl::GLRenderer3D;

        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_ebo;

        size_t m_indexCount = 0;

    public:
        GLMesh(const VertexBuffer& vertices, const IndexBuffer& indices);
        virtual ~GLMesh() override;
    };

}

#endif // __opengl__
