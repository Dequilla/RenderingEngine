#ifdef __opengl__

#include "platform/opengl/gl_model.hpp"
#include "platform/opengl/opengl.hpp"

namespace rg::opengl
{

    GLMesh::GLMesh(const VertexBuffer& vertices, const IndexBuffer& indices)
    {
        gl::glGenVertexArrays(1, &m_vao);
        gl::glGenBuffers(1, &m_vbo);
        gl::glGenBuffers(1, &m_ebo);

        gl::glBindVertexArray(m_vao);

        gl::glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        gl::glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(rg::Index), indices.data(), GL_STATIC_DRAW);

        gl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        gl::glEnableVertexAttribArray(0);

        gl::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        gl::glEnableVertexAttribArray(1);

        gl::glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        gl::glEnableVertexAttribArray(1);

        gl::glBindVertexArray(0);

        m_indexCount = indices.size();
    }

    GLMesh::~GLMesh()
    {
        gl::glDeleteBuffers(1, &m_ebo);
        gl::glDeleteBuffers(1, &m_vbo);
        gl::glDeleteVertexArrays(1, &m_vao);
    }

}

#endif // __opengl__
