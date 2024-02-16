#include "graphics/model_formats/wavefront_obj.hpp"

#include <fstream>
#include <optional>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

namespace rg
{
    inline std::vector<std::string> splitString(const std::string& str, const char& delimiter = ' ')
    {
        std::stringstream ss(str);
        std::string element;
        std::vector<std::string> elements;
        while(std::getline(ss, element, delimiter))
        {
            elements.push_back(element);
        }
        return elements;
    }

    std::optional<rg::Vertex> WavefrontOBJ_ModelLoader::processVertex(const std::string& line) const
    {
        // Format:
        // v 0.123 0.234 0.345 1.0

        std::vector<std::string> components = splitString(line, ' ');

        if(components.empty() || components.size() < 3)
            return std::nullopt;

        std::vector<float> fc;
        for( std::string& comp : components)
        {
            try
            {
                fc.push_back(std::stof(comp));
            }
            catch(std::invalid_argument e)
            {
                continue;
            }
        }

        if(fc.size() < 3)
        {
            // TODO: Tell user about model error in some type of debug mode
            return std::nullopt;
        }

        return rg::Vertex({fc[0], fc[1], fc[2]});
    }

    std::optional<std::vector<rg::Index>> WavefrontOBJ_ModelLoader::processIndex(const std::string& line) const
    {
        // Formats:
        // f v1 v2 v3 ....
        // f v1/vt1 v2/vt2 v3/vt3 ...
        // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
        // f v1//vn1 v2//vn2 v3//vn3 ...

        std::vector<std::string> components = splitString(line, ' ');
        
        if(components.empty() || components.size() < 3)
            return std::nullopt;

        std::vector<rg::Index> indices;
        for( std::string& comp : components )
        {
            if(comp.size() < 1) continue;
            
            std::vector<std::string> indicesStr = splitString(comp, '/');
            if(indicesStr.empty())
                continue;

            for( std::string& indexStr : indicesStr )
            {
                try
                {
                    rg::Index index = std::stoull(indexStr) - 1;
                    assert(index < 0 && "Negative index in wavefront model loaded.");
                    indices.push_back(index);
                    break; // TODO Break for now, other types of indices will be handled later 
                }
                catch(std::invalid_argument e)
                {
                    continue;
                }
            }
        }

        if(indices.empty()) 
            return std::nullopt;
        else
        {
            // TODO handle better
            if(indices.size() > 4 || indices.size() < 3)
                std::cout << "Model has unsupported face-layout. Triangles and quads supported." << std::endl;

            if(indices.size() > 3)
            {
                indices = rg::triangulate(indices);
            }

            return indices;
        }
    }

    std::optional<rg::WavefrontOBJ_ModelLoader::ObjectGroup> WavefrontOBJ_ModelLoader::processObjectGroup(const std::string& line) const
    {
        // This is assumed to be how meshse are defined
        // Format: 
        // o [group name]

        std::vector<std::string> components = splitString(line, ' ');
        if(components.size() < 2)
            return std::nullopt;

        components.erase(components.begin()); // o removed

        for( std::string& comp : components )
        {
            if(!comp.empty())
            {
                return rg::WavefrontOBJ_ModelLoader::ObjectGroup {
                    .name = comp
                };
            }
        }

        // TODO: Missing name, send error?
        return std::nullopt;
    }

    void WavefrontOBJ_ModelLoader::finishCurrentMesh()
    {
        if(!m_currVertices.empty() && !m_currIndices.empty())
        {
            std::cout << "Total indices: " << m_currIndices.size() << std::endl;
            m_currModel.add(m_currVertices, m_currIndices);    
            m_currVertices.clear();
            m_currIndices.clear();
        }
    }

    rg::WavefrontOBJ_ModelLoader::LineData WavefrontOBJ_ModelLoader::processStrLine(const std::string& line) const
    {
        if(line.empty() || line.size() <= 3)
            return std::nullopt;
        
        if(line[0] == 'v' && line[1] == ' ')
        {
            // Parse vertex
            std::optional<rg::Vertex> vert = processVertex(line);
            if(!vert.has_value())
                return std::nullopt;
            return vert.value();

        }
        else if(line[0] == 'f' && line[1] == ' ')
        {
            // Parse index
            std::optional<std::vector<rg::Index>> inde = processIndex(line);
            if(!inde.has_value())
                return std::nullopt;
            return inde.value();
        }
        else if(line[0] == 'o' && line[1] == ' ')
        {
            // New object (mesh)
            std::optional<rg::WavefrontOBJ_ModelLoader::ObjectGroup> ogroup = processObjectGroup(line);           
            if(!ogroup.has_value())
                return std::nullopt;
            return ogroup.value();
        }
        else
        {
            // A non supported feature (currently)
            static bool notSupported = true;
            if(notSupported)
            {
                notSupported = false;
                std::cout << "Warning: One of the loaded models had a non-supported feature (currently .obj only supports vertices and indexes)" << std::endl;
            }
            
            return std::nullopt;
        }

        return std::nullopt;
    }

    void WavefrontOBJ_ModelLoader::processLineData(const LineData& data)
    {
        if(std::holds_alternative<rg::Vertex>(data))
        {
            m_currVertices.push_back(std::get<rg::Vertex>(data));
        }
        else if(std::holds_alternative<std::vector<rg::Index>>(data))
        {
            std::vector<rg::Index> indices = std::get<std::vector<rg::Index>>(data);

            for( rg::Index index : indices  )
                m_currIndices.push_back(index);
        }
        else if(std::holds_alternative<rg::WavefrontOBJ_ModelLoader::ObjectGroup>(data))
        {
            finishCurrentMesh();
        }

    }

    std::optional<rg::Model> WavefrontOBJ_ModelLoader::load(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        if(!file.is_open())
            return std::nullopt;

        m_currModel = rg::Model();
        m_currVertices.clear();
        m_currIndices.clear();

        std::string line;
        while(std::getline(file, line)) 
        {
            LineData data = processStrLine(line);
            processLineData(data);
        }
        
        file.close();

        if(!m_currVertices.empty() && !m_currIndices.empty())
        {
            finishCurrentMesh();
        }

        if(m_currModel.count() > 0)
            return std::move(m_currModel);

        return std::nullopt;
    }

}
