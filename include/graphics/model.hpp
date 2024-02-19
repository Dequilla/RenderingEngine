#pragma once
#include <memory>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <iostream>

namespace rg
{

    using Index = uint32_t;

    struct Vertex
    {
        struct Position
        {
            float x;
            float y;
            float z;
        } position;

        struct Normal
        {
            float x;
            float y;
            float z;
        } normal;
    };

    using VertexBuffer = std::vector<Vertex>;
    using IndexBuffer = std::vector<Index>;

    template<typename Type>
    std::vector<Type> triangulate(const std::vector<Type>& buffer)
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
        if(buffer.size() % 4 != 0)
        {
            std::cout << "Warning: Can not triangulate buffer, indices not divisble by 4 (already triangles?)." << std::endl;
            return buffer;
        }

        std::vector<Type> newBuffer;

        for( size_t index = 0; (index + 3) < buffer.size(); index += 4 )
        {
            // First triangle
            newBuffer.push_back(buffer[index]);
            newBuffer.push_back(buffer[index + 1]);
            newBuffer.push_back(buffer[index + 3]);

            // Second triangle
            newBuffer.push_back(buffer[index + 3]);
            newBuffer.push_back(buffer[index + 1]);
            newBuffer.push_back(buffer[index + 2]);
        }
        
        return newBuffer;
    }

    class Mesh
    {
    public:
        virtual ~Mesh() = default;

        static std::unique_ptr<Mesh> create(const VertexBuffer& vertices, const IndexBuffer& indices);
    };

    // TODO
    class Model
    {
    protected:
        std::vector<std::unique_ptr<Mesh>> m_meshes;

    public:
        inline void add(const VertexBuffer& vertices, const IndexBuffer& indices)
        {
            m_meshes.push_back(rg::Mesh::create(vertices, indices));
        }

        inline size_t count() const
        {
            return m_meshes.size();
        }

        inline const std::vector<std::unique_ptr<Mesh>>& meshes() const
        {
            return m_meshes;
        }
    };

    class ModelLoader
    {
    public:
        virtual std::optional<rg::Model> load(const std::filesystem::path& path) = 0;
    };

}
