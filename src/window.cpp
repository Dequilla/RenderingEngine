#include "window.hpp"

#if defined(__linux__) && defined(__opengl__)
#include "platform/x11/x11_window.hpp"
#define RG_WINDOW_IMPL WindowImplX11
#endif

namespace rg
{
    bool WindowImpl::popEvent(Event& event)
    {
        if(m_eventQueue.empty()) 
            return false;

        event = m_eventQueue.front();
        m_eventQueue.pop_front();
        return true;
    }
    
    bool WindowImpl::hasEvents() const
    {
        return !m_eventQueue.empty();
    }

    Window::Window(std::string title, uint32_t width, uint32_t height)
    {
        m_impl = std::make_unique<RG_WINDOW_IMPL>(title, width, height);
    }

    Window::~Window()
    {
    }

    void Window::setTitle(const std::string& str)
    {
        m_impl->setTitle(str);       
    }

    void Window::grabMouse(bool grab)
    {
        m_impl->grabMouse(grab); 
    }

    void Window::setCursorVisible(bool visible)
    {
        m_impl->setCursorVisible(visible);
    }

    void Window::close()
    {
        m_impl->close();
    }

    bool Window::isOpen()
    {
       return m_impl->isOpen(); 
    }
    
    bool Window::pollEvent(Event& event)
    {
        if(!m_impl->hasEvents())
            m_impl->processEvents();

        return m_impl->popEvent(event);
    }

    void Window::initFrame()
    {
        m_impl->initFrame();
    }

    void Window::presentFrame()
    {
        m_impl->presentFrame();
    }

}
