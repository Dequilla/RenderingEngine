#include "window.hpp"

#ifdef __linux__
#include <stdexcept>
#include <cassert>

#include "X11/Xlib.h"
#include <GL/gl.h>
#include <GL/glx.h>

namespace rg
{

    struct WindowImpl
    {
        ::Display* display;
	    ::Window window;
	    ::Screen* screen;
	    int screenId;
		Atom wm_delete_window;
        GLXContext glContext;

        bool isOpen = false;
    };

    Window::Window(std::string title, uint32_t width, uint32_t height)
    {
        m_windowImpl = new WindowImpl();
		
		m_windowImpl->display = XOpenDisplay(NULL);
        if (NULL == m_windowImpl->display) {
            std::runtime_error("Failed to initialize display");
        }
        m_windowImpl->screen = DefaultScreenOfDisplay(m_windowImpl->display);
	    m_windowImpl->screenId = DefaultScreen(m_windowImpl->display);

		GLint majorGLX = 0, minorGLX = 0;
	    glXQueryVersion(m_windowImpl->display, &majorGLX, &minorGLX);
	    if (majorGLX <= 1 && minorGLX < 2) {
		    throw std::runtime_error("GLX 1.2 or greater is required.");
	    }
        
        // GLX, create XVisualInfo, this is the minimum visuals we want
	    GLint glxAttribs[] = {
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
		visualInfo = glXChooseVisual(m_windowImpl->display, DefaultScreen(m_windowImpl->display), glxAttribs);
	    if (visualInfo == 0) {
            throw std::runtime_error("Could not create correct visual window");
	    }
        
        // Open the window
		XSetWindowAttributes m_attrs;
	    m_attrs.border_pixel = BlackPixel(m_windowImpl->display, m_windowImpl->screenId);
	    m_attrs.background_pixel = WhitePixel(m_windowImpl->display, m_windowImpl->screenId);
	    m_attrs.override_redirect = True;
        m_attrs.colormap = XCreateColormap(m_windowImpl->display, RootWindow(m_windowImpl->display, m_windowImpl->screenId), visualInfo->visual, AllocNone);
        m_attrs.event_mask = KeyPressMask | KeyReleaseMask | PointerMotionMask; 

        m_windowImpl->window = XCreateWindow(m_windowImpl->display, RootWindow(m_windowImpl->display, m_windowImpl->screenId), 0, 0, width, height, 0, CopyFromParent, InputOutput, CopyFromParent, CWEventMask, &m_attrs);

        if (None == m_windowImpl->window) {
            XCloseDisplay(m_windowImpl->display);
            std::runtime_error("Failed to create window");
        }

        // Create GLX OpenGL context
	    m_windowImpl->glContext = glXCreateContext(m_windowImpl->display, visualInfo, NULL, GL_TRUE);
	    glXMakeCurrent(m_windowImpl->display, m_windowImpl->window, m_windowImpl->glContext);

	    // Show the window
	    XClearWindow(m_windowImpl->display, m_windowImpl->window);
	    XMapRaised(m_windowImpl->display, m_windowImpl->window);

        m_windowImpl->wm_delete_window = XInternAtom(m_windowImpl->display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_windowImpl->display, m_windowImpl->window, &m_windowImpl->wm_delete_window, 1);

        XMapWindow(m_windowImpl->display, m_windowImpl->window);
        XFlush(m_windowImpl->display);

        m_windowImpl->isOpen = true;
    }

    Window::~Window()
    {
        glXDestroyContext(m_windowImpl->display, m_windowImpl->glContext);
        XDestroyWindow(m_windowImpl->display, m_windowImpl->window);
        XCloseDisplay(m_windowImpl->display);

        m_windowImpl->isOpen = false;
        delete m_windowImpl;
        m_windowImpl = nullptr;
    }

    void Window::close()
    {
        m_windowImpl->isOpen = false;
    }

    bool Window::isOpen()
    {
        if(!m_windowImpl) return false;
        return m_windowImpl->isOpen;
    }
    
    bool Window::pollEvent(Event& event)
    {
        if(!m_windowImpl) return false;
        if(!m_windowImpl->display) return false;

        XEvent xevent;
        if(XPending(m_windowImpl->display))
        {
            XNextEvent(m_windowImpl->display, &xevent);
            switch(xevent.type) {
                case ClientMessage:
                    if(xevent.xclient.data.l[0] == m_windowImpl->wm_delete_window) {
                        event.type = EventType::Close;
                        close();
                        return true;
                    }
                break;
            }
        }

        return false;
    }

    void Window::initFrame()
    {
        glXMakeCurrent(m_windowImpl->display, m_windowImpl->window, m_windowImpl->glContext);
    }

    void Window::presentFrame()
    {
        glXSwapBuffers(m_windowImpl->display, m_windowImpl->window);
    }

    void Window::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }


}
#endif
