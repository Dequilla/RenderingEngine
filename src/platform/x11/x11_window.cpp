#include "platform/x11/x11_window.hpp"

#if defined(__x11__) && defined(__opengl__)

namespace rg
{
    WindowImplX11::WindowImplX11(std::string title, uint32_t width, uint32_t height)
        : WindowImpl(title, width, height)
    {
        m_display = XOpenDisplay(NULL);
        if (NULL == m_display) 
        {
            std::runtime_error("Failed to initialize display");
        }
        m_screen = DefaultScreenOfDisplay(m_display);
        m_screenId = DefaultScreen(m_display);

        GLint majorGLX = 0, minorGLX = 0;
        glXQueryVersion(m_display, &majorGLX, &minorGLX);
        if (majorGLX <= 1 && minorGLX < 2) 
        {
            throw std::runtime_error("GLX 1.2 or greater is required.");
        }

        // GLX, create XVisualInfo, this is the minimum visuals we want
        GLint glxAttribs[] = 
        {
            GLX_RGBA,
            GLX_DOUBLEBUFFER,
            GLX_DEPTH_SIZE,     24,
            GLX_STENCIL_SIZE,   8,
            GLX_RED_SIZE,       8,
            GLX_GREEN_SIZE,     8,
            GLX_BLUE_SIZE,      8,
            GLX_SAMPLE_BUFFERS, 0,
            GLX_SAMPLES,        0,
            None
        };
        
        XVisualInfo* visualInfo;
        visualInfo = glXChooseVisual(m_display, DefaultScreen(m_display), glxAttribs);
        if (visualInfo == 0) 
        {
            throw std::runtime_error("Could not create correct visual window");
        }

        // Open the window
        XSetWindowAttributes m_attrs;
        m_attrs.border_pixel = BlackPixel(m_display, m_screenId);
        m_attrs.background_pixel = WhitePixel(m_display, m_screenId);
        m_attrs.override_redirect = True;
        m_attrs.colormap = XCreateColormap(m_display, RootWindow(m_display, m_screenId), visualInfo->visual, AllocNone);
        m_attrs.event_mask = KeyPressMask | KeyReleaseMask | PointerMotionMask; 

        m_window = XCreateWindow(m_display, RootWindow(m_display, m_screenId), 0, 0, width, height, 0, CopyFromParent, InputOutput, CopyFromParent, CWEventMask, &m_attrs);

        if (None == m_window) 
        {
            XCloseDisplay(m_display);
            std::runtime_error("Failed to create window");
        }

        setTitle(title);
        m_width = width;
        m_height = height;

        // Create GLX OpenGL context
        m_glContext = glXCreateContext(m_display, visualInfo, NULL, GL_TRUE);
        glXMakeCurrent(m_display, m_window, m_glContext);
    
        // Show the window
        XClearWindow(m_display, m_window);
        XMapRaised(m_display, m_window);

        m_wm_delete_window = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_window, &m_wm_delete_window, 1);

        XMapWindow(m_display, m_window);
        XFlush(m_display);

        m_isOpen = true;
    }

    WindowImplX11::~WindowImplX11()
    {
        glXDestroyContext(m_display, m_glContext);
        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);

        m_isOpen = false;
    }

    void WindowImplX11::setTitle(const std::string& str)
    {
        char* cstr = new char[str.size()];
        std::memcpy(cstr, str.c_str(), str.size());

        XTextProperty tp;
        int res = XmbTextListToTextProperty(m_display, &cstr, 1, XICCEncodingStyle::XStringStyle, &tp);
        assert(res == Success && "Likely invalid window title encoding.");
        delete[] cstr;

        XSetWMName(m_display, m_window, &tp);
        XFree(tp.value);
    }

    bool WindowImplX11::grabMouse(bool grab)
    {
        if(grab)
        {
            const unsigned int mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            int result;
            for (int attempts = 0; attempts < 100; attempts++) {
                result = ::XGrabPointer(
                    m_display,
                    m_window, 
                    True, 
                    None, 
                    GrabModeAsync, 
                    GrabModeAsync, 
                    m_window, 
                    None, 
                    CurrentTime
                );

                if(result == GrabSuccess)
                    break;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            if(result == GrabSuccess)
            {
                m_mouseGrabbed = true;
                return true;
            }
            else
            {
                m_mouseGrabbed = false;
                return false;
            }
        }
        else
        {
            // TODO ungrab
            throw std::runtime_error("not implemented");
            return false;
        }
    }

    void WindowImplX11::setCursorVisible(bool visible)
    {
        // XDefineCursor(m_windowImpl->display, m_windowImpl->window, visible ? m_lastCursor : m_hiddenCursor);
        // XFlush(m_display.get());
        throw std::runtime_error("not implemented \"setCursorVisible\"");
    }

    void WindowImplX11::close() 
    {
        m_isOpen = false;
    }
    
    bool WindowImplX11::isOpen() 
    {
        return m_isOpen;
    }

    void WindowImplX11::processEvents() 
    {
        if(!m_display) return;

        XEvent xevent;
        rg::Event event;
        while(XPending(m_display))
        {
            XNextEvent(m_display, &xevent);
            switch(xevent.type) {

                // Client messages (ex. window)
                case ClientMessage:
                    if(xevent.xclient.data.l[0] == m_wm_delete_window) {
                        event.type = EventType::Close;
                    }
                break;

                // Motions (ex. mouse move)
                case MotionNotify:
                    event.type = EventType::Motion;
                    event.motion.deltax = xevent.xmotion.x - m_motionLast_x;
                    event.motion.deltay = xevent.xmotion.y - m_motionLast_y;

                    event.motion.x = xevent.xmotion.x;
                    event.motion.y = xevent.xmotion.y;

                    m_motionLast_x = event.motion.x;
                    m_motionLast_y = event.motion.y;

                    // TODO
                    if(m_mouseGrabbed)
                    {
                        //XWarpPointer(m_windowImpl->display, None, m_windowImpl->window, 0, 0, 0, 0, m_width / 2, m_height / 2);
                    }
                break;
                
            } // switch(xevent.type)
              
            m_eventQueue.push_back(event);
        } // while(NextEvent)
    }

    void WindowImplX11::initFrame() 
    {
        glXMakeCurrent(m_display, m_window, m_glContext);
    }

    void WindowImplX11::presentFrame() 
    {
        glXSwapBuffers(m_display, m_window);
    }

}

#endif // __x11__ && __opengl__
