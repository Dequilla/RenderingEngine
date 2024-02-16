#pragma once

#include "color.hpp"
#include "model.hpp"

#include <cstdint>
#include <memory>

namespace rg
{
    class Renderer
    {
    public:
        virtual void init() = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void setClearColor(color::RGBAf color) = 0;
        virtual void clear() = 0;
    };

    class Renderer3D : public Renderer
    {
    public:
        virtual void init() = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void setClearColor(color::RGBAf color) = 0;
        virtual void clear() = 0;

        virtual void draw(const Mesh& mesh) = 0;
        virtual void draw(const Model& model) = 0;

        static std::unique_ptr<Renderer3D> create();
    };

}
