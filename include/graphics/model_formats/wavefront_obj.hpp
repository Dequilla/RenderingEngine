#pragma once

#include <variant>
#include <optional>

#include "graphics/model.hpp"

namespace rg
{   
    namespace wavefront
    {

        struct Vertex
        {
            float x;
            float y;
            float z;
        };

        struct Normal
        {
            float x;
            float y;
            float z;
        };

        struct TexCoord
        {
            float x;
            float y;
        };

        struct Index
        {
            uint32_t vertex;
            uint32_t texcoord;
            uint32_t normal;
            // TODO: Add tex coord index
        };
    }


    class WavefrontOBJ_ModelLoader : public rg::ModelLoader
    {
    protected:
        rg::Model m_currModel;

        std::vector<rg::wavefront::Vertex> m_currVertices;
        std::vector<rg::wavefront::Normal> m_currNormals;
        std::vector<rg::wavefront::TexCoord> m_currTexCoords;
        std::vector<rg::wavefront::Index> m_currIndices;

        struct ObjectGroup 
        {
            std::string name;
        };

        using LineData = std::variant<rg::wavefront::Vertex, rg::wavefront::Normal, rg::wavefront::TexCoord, std::vector<rg::wavefront::Index>, ObjectGroup, std::nullopt_t>;

        std::optional<rg::wavefront::Vertex> processVertex(const std::string& line) const;
        std::optional<rg::wavefront::Normal> processNormal(const std::string& line) const;
        std::optional<rg::wavefront::TexCoord> processTexCoord(const std::string& line) const;
        std::optional<std::vector<rg::wavefront::Index>> processIndex(const std::string& line) const;
        std::optional<rg::WavefrontOBJ_ModelLoader::ObjectGroup> processObjectGroup(const std::string& line) const;

        void finishCurrentMesh();

        LineData processStrLine(const std::string& line) const;
        void processLineData(const LineData& data);

    public:
        std::optional<rg::Model> load(const std::filesystem::path& path) override;
    };

}
