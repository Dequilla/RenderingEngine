#pragma once
#include <cstdint>

namespace rg::color 
{

    template<typename Component>
    struct RGB
    {
        Component r;
        Component g;
        Component b;
    };

    using RGBf = RGB<float>;
    using RGBd = RGB<double>;
    using RGB8 = RGB<uint8_t>;
    using RGB16 = RGB<uint16_t>;
    using RGB32 = RGB<uint32_t>;
    
    template<typename Component>
    struct RGBA
    {
        Component r;
        Component g;
        Component b;
        Component a;
    };

    using RGBAf = RGBA<float>;
    using RGBAd = RGBA<double>;
    using RGBA8 = RGBA<uint8_t>;
    using RGBA16 = RGBA<uint16_t>;
    using RGBA32 = RGBA<uint32_t>;
    
}
