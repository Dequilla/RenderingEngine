#pragma once

#include "graphics/renderer.hpp"

#ifdef __opengl__

namespace rg::opengl
{
    class GLRenderer3D : public rg::Renderer3D
    {
    public:
        virtual void init() override;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void setClearColor(color::RGBAf color) override;
        virtual void clear() override;

        virtual void draw(const Mesh& mesh) override;
    };
}

#endif // __opengl__
