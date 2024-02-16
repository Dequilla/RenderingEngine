#include "graphics/model.hpp"

#include <cassert>
#include <iostream>

#ifdef __opengl__
#include "platform/opengl/gl_model.hpp"
#define RG_MODEL_IMPL rg::opengl::GLMesh
#endif

namespace rg
{
    IndexBuffer triangulate(const IndexBuffer& indexBuffer)
    {
        // p1---p2
        // |  ./|
        // | /  |
        // p4---p3
        // 
        // 
        // T1 = p1, p2, p4 
        // T2 = p4, p2, p3
        //
        // From quad to triangles
        if(indexBuffer.size() % 4 != 0)
        {
            std::cout << "Warning: Can not triangulate buffer, indices not divisble by 4 (already triangles?)." << std::endl;
            return indexBuffer;
        }

        IndexBuffer newBuffer;

        for( size_t index = 0; (index + 3) < indexBuffer.size(); index += 4 )
        {
            // First triangle
            newBuffer.push_back(indexBuffer[index]);
            newBuffer.push_back(indexBuffer[index + 1]);
            newBuffer.push_back(indexBuffer[index + 3]);

            // Second triangle
            newBuffer.push_back(indexBuffer[index + 3]);
            newBuffer.push_back(indexBuffer[index + 1]);
            newBuffer.push_back(indexBuffer[index + 2]);
        }
        
        return newBuffer;
    }

    std::unique_ptr<Mesh> Mesh::create(const VertexBuffer& vertices, const IndexBuffer& indices)
    {
        return std::make_unique<RG_MODEL_IMPL>(vertices, indices);
    }

}
