#pragma once

#include <variant>
#include <optional>

#include "graphics/model.hpp"

namespace rg
{   

    class WavefrontOBJ_ModelLoader : public rg::ModelLoader
    {
    protected:
        rg::Model m_currModel;
        VertexBuffer m_currVertices;
        IndexBuffer m_currIndices;         

        struct ObjectGroup 
        {
            std::string name;
        };

        using LineData = std::variant<rg::Vertex, std::vector<rg::Index>, ObjectGroup, std::nullopt_t>;

        std::optional<rg::Vertex> processVertex(const std::string& line) const;
        std::optional<std::vector<rg::Index>> processIndex(const std::string& line) const;
        std::optional<rg::WavefrontOBJ_ModelLoader::ObjectGroup> processObjectGroup(const std::string& line) const;

        void finishCurrentMesh();

        LineData processStrLine(const std::string& line) const;
        void processLineData(const LineData& data);

    public:
        std::optional<rg::Model> load(const std::filesystem::path& path) override;
    };

}
