#pragma once
#include <string>
#include <cstdint>
#include <deque>
#include <memory>

#include "event.hpp"
#include "color.hpp"

namespace rg
{

    class WindowImpl
    {
    protected:
        std::deque<Event> m_eventQueue;

        bool m_mouseGrabbed = false;
        uint32_t m_width = 0;
        uint32_t m_height = 0;

    public:
        WindowImpl(std::string title, uint32_t width, uint32_t height) {}
        virtual ~WindowImpl() = default;

        virtual void setTitle(const std::string& str) = 0;
        virtual void grabMouse(bool grab) = 0;
        virtual void setCursorVisible(bool visible) = 0;

        virtual void close() = 0;

        virtual bool isOpen() = 0;

        virtual void processEvents() = 0;
        bool popEvent(Event& event);
        bool hasEvents() const;

        virtual void initFrame() = 0;
        virtual void presentFrame() = 0;
    };

    class Window
    {
        std::unique_ptr<WindowImpl> m_impl;

    public:
        Window(std::string title, uint32_t width, uint32_t height);
        ~Window();

        void setTitle(const std::string& str);
        void grabMouse(bool grab);
        void setCursorVisible(bool visible);

        void close();

        bool isOpen();

        bool popEvent(Event& event);
        bool pollEvent(Event& event);

        void initFrame();
        void presentFrame();
    };

}
