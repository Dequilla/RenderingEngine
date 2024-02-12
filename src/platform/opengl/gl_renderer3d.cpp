#include "renderer.hpp"

#ifdef __opengl__

#include "model.hpp"
#include "platform/opengl/opengl.hpp"
#include "platform/opengl/gl_model.hpp"
#include "platform/opengl/gl_renderer3d.hpp"

namespace rg::opengl
{

    void GLRenderer3D::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
    }

    void GLRenderer3D::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void GLRenderer3D::setClearColor(color::RGBAf color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void GLRenderer3D::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderer3D::draw(const Mesh& mesh)
    {
        const rg::opengl::GLMesh& glmesh = static_cast<const rg::opengl::GLMesh&>(mesh); 

        gl::bindVertexArray(glmesh.m_vao);
        gl::drawElements(GL_TRIANGLES, glmesh.m_indexCount, GL_UNSIGNED_INT, 0);
        gl::bindVertexArray(0);
    }

}

#endif // __opengl__
