#pragma once
#include <string>
#include <cstdint>

#include "event.hpp"

namespace rg
{

    class WindowImpl;

    class Window
    {
        WindowImpl* m_windowImpl;

    public:
        Window(std::string title, uint32_t width, uint32_t height);
        ~Window();

        void close();

        bool isOpen();

        bool pollEvent(Event& event);

        void initFrame();
        void presentFrame();
        void clear();
    };

}
