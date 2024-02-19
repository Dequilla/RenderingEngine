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

    std::optional<rg::wavefront::Vertex> WavefrontOBJ_ModelLoader::processVertex(const std::string& line) const
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
            assert(false && "Error in WavefrontOBJ_ModelLoader::processVertex()");
            return std::nullopt;
        }

        return rg::wavefront::Vertex({fc[0], fc[1], fc[2]});
    }

    std::optional<rg::wavefront::Normal> WavefrontOBJ_ModelLoader::processNormal(const std::string& line) const
    {
        // Normals:
        // vn 1.2 1.2 1.2
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
            assert(false && "Error in WavefrontOBJ_ModelLoader::processNormal()");
            return std::nullopt;
        }

        return rg::wavefront::Normal({fc[0], fc[1], fc[2]});
    }

    std::optional<std::vector<rg::wavefront::Index>> WavefrontOBJ_ModelLoader::processIndex(const std::string& line) const
    {
        // Formats:
        // f v1 v2 v3 ....
        // f v1/vt1 v2/vt2 v3/vt3 ...
        // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
        // f v1//vn1 v2//vn2 v3//vn3 ...

        std::vector<std::string> components = splitString(line, ' ');
        
        if(components.empty() || components.size() < 3)
            return std::nullopt;

        std::vector<rg::wavefront::Index> indices;
        for( std::string& comp : components )
        {
            if(comp.size() < 1) continue;
            
            std::vector<std::string> indicesStr = splitString(comp, '/');
            if(indicesStr.empty() || indicesStr[0].find('f') != std::string::npos)
                continue;

            try
            {
                rg::wavefront::Index index; 

                if(indicesStr.size() >= 1)
                {
                    // Only vertex
                    index.vertex = std::stoull(indicesStr.at(0));
                }
                
                if(indicesStr.size() == 2)
                {
                    // TexCoord also
                    index.texcoord = std::stoull(indicesStr.at(1));
                }
                
                if(indicesStr.size() >= 3)
                {

                    // TexCoords and Normals too
                    try
                    {
                        // Could be empty so just ignore if the case
                        index.texcoord = std::stoull(indicesStr.at(1));
                    }
                    catch(std::invalid_argument e)
                    {
                    }

                    // Normal
                    index.normal = std::stoull(indicesStr.at(2));
                }

                indices.push_back(index);
            } 
            catch(std::invalid_argument e)
            {
                std::cout << "failed with on index parse => " << comp << std::endl;
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
                indices = rg::triangulate<rg::wavefront::Index>(indices);
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
        // TODO: Construct rg::Vertex from list of vertices, normals and indices.
       
        if(!m_currVertices.empty() && !m_currIndices.empty())
        {
            rg::VertexBuffer vb;
            rg::IndexBuffer ib;
            for( rg::wavefront::Index& index : m_currIndices)
            {
                // All indexes in OBJ are 1-based.
                
                rg::Vertex vert;

                rg::wavefront::Vertex wvert = m_currVertices.at(index.vertex - 1);
                vert.position = { wvert.x, wvert.y, wvert.z };

                assert(!m_currNormals.empty() && "No normals loaded for a model...");
                rg::wavefront::Normal wnorm = m_currNormals.at(index.normal - 1);
                vert.normal = { wnorm.x, wnorm.y, wnorm.z };

                // TODO: TexCoords

                vb.push_back(vert);
                ib.push_back(vb.size() - 1);
            }

            m_currVertices.clear();
            m_currIndices.clear();
            m_currNormals.clear();

            m_currModel.add(vb, ib);    
        }
  
    }

    rg::WavefrontOBJ_ModelLoader::LineData WavefrontOBJ_ModelLoader::processStrLine(const std::string& line) const
    {
        if(line.empty() || line.size() <= 3)
            return std::nullopt;
        
        if(line[0] == 'v' && line[1] == ' ')
        {
            // Parse vertex
            std::optional<rg::wavefront::Vertex> vert = processVertex(line);
            if(!vert.has_value())
                return std::nullopt;
            return vert.value();

        }
        else if(line[0] == 'v' && line[1] == 'n')
        {
            std::optional<rg::wavefront::Normal> norm = processNormal(line);
            if(!norm.has_value())
                return std::nullopt;
            return norm.value();
        }
        else if(line[0] == 'f' && line[1] == ' ')
        {
            // Parse index
            std::optional<std::vector<rg::wavefront::Index>> inde = processIndex(line);
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
        if(std::holds_alternative<rg::wavefront::Vertex>(data))
        {
            m_currVertices.push_back(std::get<rg::wavefront::Vertex>(data));
        }
        else if(std::holds_alternative<rg::wavefront::Normal>(data))
        {
            m_currNormals.push_back(std::get<rg::wavefront::Normal>(data));
        }
        else if(std::holds_alternative<std::vector<rg::wavefront::Index>>(data))
        {
            std::vector<rg::wavefront::Index> indices = std::get<std::vector<rg::wavefront::Index>>(data);

            for( rg::wavefront::Index index : indices)
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
        m_currNormals.clear();
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
