#pragma once

#if defined(__x11__) && defined(__opengl__)
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <chrono>
#include <thread>

#include "X11/Xlib.h"
#include <GL/gl.h>
#include <GL/glx.h>

#include "window.hpp"

namespace rg
{
    
   class WindowImplX11 : public WindowImpl
   {
      ::Display* m_display;
      ::Window m_window;
      ::Screen* m_screen;
      int m_screenId;
      Atom m_wm_delete_window;
      GLXContext m_glContext;

      bool m_isOpen = false;

      // Events
      uint64_t m_motionLast_x = 0;
      uint64_t m_motionLast_y = 0;

   public:
      WindowImplX11(std::string title, uint32_t width, uint32_t height);
      virtual ~WindowImplX11() override;

      virtual void setTitle(const std::string& str) override;
      virtual bool grabMouse(bool grab) override;
      virtual void setCursorVisible(bool visible) override;

      virtual void close() override;
         
      virtual bool isOpen() override;

      virtual void processEvents() override;

      virtual void initFrame() override;
      virtual void presentFrame() override;
   };

}

#endif // __x11__
