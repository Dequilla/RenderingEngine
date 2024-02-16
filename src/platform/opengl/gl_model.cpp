#ifdef __opengl__

#include "platform/opengl/gl_model.hpp"
#include "platform/opengl/opengl.hpp"

namespace rg::opengl
{

    GLMesh::GLMesh(const VertexBuffer& vertices, const IndexBuffer& indices)
    {
        gl::genVertexArrays(1, &m_vao);
        gl::genBuffers(1, &m_vbo);
        gl::genBuffers(1, &m_ebo);

        gl::bindVertexArray(m_vao);

        gl::bindBuffer(GL_ARRAY_BUFFER, m_vbo);
        gl::bufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        gl::bufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(rg::Index), indices.data(), GL_STATIC_DRAW);

        gl::vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        gl::enableVertexAttribArray(0);

        gl::bindVertexArray(0);

        m_indexCount = indices.size();
    }

    GLMesh::~GLMesh()
    {
        gl::deleteBuffers(1, &m_ebo);
        gl::deleteBuffers(1, &m_vbo);
        gl::deleteVertexArrays(1, &m_vao);
    }

}

#endif // __opengl__
