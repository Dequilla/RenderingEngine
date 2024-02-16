#pragma once
#include <memory>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <optional>

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
    };

    using VertexBuffer = std::vector<Vertex>;
    using IndexBuffer = std::vector<Index>;

    IndexBuffer triangulate(const IndexBuffer& indexBuffer);

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
