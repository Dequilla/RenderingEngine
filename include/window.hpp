#pragma once
#include <string>
#include <cstdint>

#include "event.hpp"
#include "color.hpp"

namespace rg
{

    class WindowImpl;

    class Window
    {
        WindowImpl* m_windowImpl;

    public:
        Window(std::string title, uint32_t width, uint32_t height);
        ~Window();

        void setTitle(const std::string& str);
        void setClearColor(color::RGBAf color);

        void close();

        bool isOpen();

        bool pollEvent(Event& event);

        void initFrame();
        void presentFrame();
        void clear();
    };

}
