#pragma once
#include <memory>
#include <vector>
#include <cstdint>

namespace rg
{

    struct Vertex
    {
        struct Position
        {
            float x;
            float y;
            float z;
        } position;
    };

    using VertexBuffer = std::vector<Vertex>;
    using IndexBuffer = std::vector<uint32_t>;

    class Mesh
    {
    public:
        virtual ~Mesh() = default;

        static std::unique_ptr<Mesh> create(const VertexBuffer& vertices, const IndexBuffer& indices);
    };

}
