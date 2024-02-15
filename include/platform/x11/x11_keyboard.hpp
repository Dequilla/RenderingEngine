#pragma once

#ifdef __x11__
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "system/keycode.hpp"

namespace rg::x11
{
   extern inline rg::KeyCode keySymToKeyCode(KeySym ks);

   inline rg::KeyCode getKeyCode(XKeyEvent* keyEvent)
   {
      for (int i = 0; i < 4; ++i)
      {
         const KeySym ks = XLookupKeysym(keyEvent, i);
         const rg::KeyCode kc = keySymToKeyCode(ks);
         if (kc != rg::KeyCode::Unknown)
             return kc;
      }

      return rg::KeyCode::Unknown;
   }

   inline rg::KeyCode keySymToKeyCode(KeySym ks)
   {
      switch(ks)
      {
         // Keypad
         case XK_KP_Space:     return rg::KeyCode::KP_Space;
         case XK_KP_Tab:       return rg::KeyCode::KP_Tab;
         case XK_KP_Enter:     return rg::KeyCode::KP_Enter;
         case XK_KP_F1:        return rg::KeyCode::KP_F1;
         case XK_KP_F2:        return rg::KeyCode::KP_F2;
         case XK_KP_F3:        return rg::KeyCode::KP_F3;
         case XK_KP_F4:        return rg::KeyCode::KP_F4;
         case XK_KP_Home:      return rg::KeyCode::KP_Home;
         case XK_KP_Left:      return rg::KeyCode::KP_Left;
         case XK_KP_Up:        return rg::KeyCode::KP_Up;
         case XK_KP_Right:     return rg::KeyCode::KP_Right;
         case XK_KP_Down:      return rg::KeyCode::KP_Down;
         case XK_KP_Page_Up:   return rg::KeyCode::KP_PageUp;
         case XK_KP_Page_Down: return rg::KeyCode::KP_PageDown;
         case XK_KP_End:       return rg::KeyCode::KP_End;
         case XK_KP_Begin:     return rg::KeyCode::KP_Begin;
         case XK_KP_Insert:    return rg::KeyCode::KP_Insert;
         case XK_KP_Delete:    return rg::KeyCode::KP_Delete;
         case XK_KP_Equal:     return rg::KeyCode::KP_Equal;
         case XK_KP_Multiply:  return rg::KeyCode::KP_Multiply;
         case XK_KP_Add:       return rg::KeyCode::KP_Add;
         case XK_KP_Separator: return rg::KeyCode::KP_Separator;
         case XK_KP_Subtract:  return rg::KeyCode::KP_Subtract;
         case XK_KP_Decimal:   return rg::KeyCode::KP_Decimal;
         case XK_KP_Divide:    return rg::KeyCode::KP_Divide;

         case XK_KP_0: return rg::KeyCode::KP_0;
         case XK_KP_1: return rg::KeyCode::KP_1;
         case XK_KP_2: return rg::KeyCode::KP_2;
         case XK_KP_3: return rg::KeyCode::KP_3;
         case XK_KP_4: return rg::KeyCode::KP_4;
         case XK_KP_5: return rg::KeyCode::KP_5;
         case XK_KP_6: return rg::KeyCode::KP_6;
         case XK_KP_7: return rg::KeyCode::KP_7;
         case XK_KP_8: return rg::KeyCode::KP_8;
         case XK_KP_9: return rg::KeyCode::KP_9;

         // Function keys
         case XK_F1: return rg::KeyCode::F1;
         case XK_F2: return rg::KeyCode::F2;
         case XK_F3: return rg::KeyCode::F3;
         case XK_F4: return rg::KeyCode::F4;
         case XK_F5: return rg::KeyCode::F5;
         case XK_F6: return rg::KeyCode::F6;
         case XK_F7: return rg::KeyCode::F7;
         case XK_F8: return rg::KeyCode::F8;
         case XK_F9: return rg::KeyCode::F9;
         case XK_F10: return rg::KeyCode::F10;
         case XK_F11: return rg::KeyCode::F11;
         case XK_F12: return rg::KeyCode::F12;
         case XK_F13: return rg::KeyCode::F13;
         case XK_F14: return rg::KeyCode::F14;
         case XK_F15: return rg::KeyCode::F15;
         case XK_F16: return rg::KeyCode::F16;
         case XK_F17: return rg::KeyCode::F17;
         case XK_F18: return rg::KeyCode::F18;
         case XK_F19: return rg::KeyCode::F19;
         case XK_F20: return rg::KeyCode::F20;
         case XK_F21: return rg::KeyCode::F21;
         case XK_F22: return rg::KeyCode::F22;
         case XK_F23: return rg::KeyCode::F23;
         case XK_F24: return rg::KeyCode::F24;
         case XK_F25: return rg::KeyCode::F25;

         // Modifiers
         case XK_Shift_L: return rg::KeyCode::LeftShift;
         case XK_Shift_R: return rg::KeyCode::RightShift;
         case XK_Control_L: return rg::KeyCode::LeftControl;
         case XK_Control_R: return rg::KeyCode::RightControl;
         case XK_Caps_Lock: return rg::KeyCode::CapsLock;
         case XK_Shift_Lock: return rg::KeyCode::ShiftLock;

         case XK_Meta_L: return rg::KeyCode::LeftMeta;
         case XK_Meta_R: return rg::KeyCode::RightMeta;
         case XK_Alt_L: return rg::KeyCode::LeftAlt;
         case XK_Alt_R: return rg::KeyCode::RightAlt;
         case XK_Super_L: return rg::KeyCode::LeftSuper;
         case XK_Super_R: return rg::KeyCode::RightSuper;
         case XK_Hyper_L: return rg::KeyCode::LeftHyper;
         case XK_Hyper_R: return rg::KeyCode::RightHyper;
                          
         // Latin 1
         case XK_space: return rg::KeyCode::Space;
         case XK_exclam: return rg::KeyCode::Exclam;
         case XK_quotedbl: return rg::KeyCode::Quotedbl;
         case XK_numbersign: return rg::KeyCode::Numbersign;
         case XK_dollar: return rg::KeyCode::Dollar;
         case XK_percent: return rg::KeyCode::Percent;
         case XK_ampersand: return rg::KeyCode::Ampersand;
         case XK_apostrophe: return rg::KeyCode::Apostrophe;
         case XK_parenleft: return rg::KeyCode::LeftParen;
         case XK_parenright: return rg::KeyCode::RightParen;
         case XK_asterisk: return rg::KeyCode::Asterisk;
         case XK_plus: return rg::KeyCode::Plus;
         case XK_comma: return rg::KeyCode::Comma;
         case XK_minus: return rg::KeyCode::Minus;
         case XK_period: return rg::KeyCode::period;
         case XK_slash: return rg::KeyCode::Slash;
         case XK_0: return rg::KeyCode::Num0;
         case XK_1: return rg::KeyCode::Num1;
         case XK_2: return rg::KeyCode::Num2;
         case XK_3: return rg::KeyCode::Num3;
         case XK_4: return rg::KeyCode::Num4;
         case XK_5: return rg::KeyCode::Num5;
         case XK_6: return rg::KeyCode::Num6;
         case XK_7: return rg::KeyCode::Num7;
         case XK_8: return rg::KeyCode::Num8;
         case XK_9: return rg::KeyCode::Num9;
         case XK_colon: return rg::KeyCode::Colon;
         case XK_semicolon: return rg::KeyCode::Semicolon;
         case XK_less: return rg::KeyCode::Less;
         case XK_equal: return rg::KeyCode::Equal;
         case XK_greater: return rg::KeyCode::Greater;
         case XK_question: return rg::KeyCode::Question;
         case XK_at: return rg::KeyCode::At;
         case XK_A: return rg::KeyCode::A;
         case XK_B: return rg::KeyCode::B;
         case XK_C: return rg::KeyCode::C;
         case XK_D: return rg::KeyCode::D;
         case XK_E: return rg::KeyCode::E;
         case XK_F: return rg::KeyCode::F;
         case XK_G: return rg::KeyCode::G;
         case XK_H: return rg::KeyCode::H;
         case XK_I: return rg::KeyCode::I;
         case XK_J: return rg::KeyCode::J;
         case XK_K: return rg::KeyCode::K;
         case XK_L: return rg::KeyCode::L;
         case XK_M: return rg::KeyCode::M;
         case XK_N: return rg::KeyCode::N;
         case XK_O: return rg::KeyCode::O;
         case XK_P: return rg::KeyCode::P;
         case XK_Q: return rg::KeyCode::Q;
         case XK_R: return rg::KeyCode::R;
         case XK_S: return rg::KeyCode::S;
         case XK_T: return rg::KeyCode::T;
         case XK_U: return rg::KeyCode::U;
         case XK_V: return rg::KeyCode::V;
         case XK_W: return rg::KeyCode::W;
         case XK_X: return rg::KeyCode::X;
         case XK_Y: return rg::KeyCode::Y;
         case XK_Z: return rg::KeyCode::Z;
         case XK_bracketleft: return rg::KeyCode::LeftBracket;
         case XK_backslash: return rg::KeyCode::Backslash;
         case XK_bracketright: return rg::KeyCode::RightBracket;
         case XK_asciicircum: return rg::KeyCode::Asciicircum;
         case XK_underscore: return rg::KeyCode::Underscore;
         case XK_grave: return rg::KeyCode::Grave;  
         case XK_a: return rg::KeyCode::a;
         case XK_b: return rg::KeyCode::b;
         case XK_c: return rg::KeyCode::c;
         case XK_d: return rg::KeyCode::d;
         case XK_e: return rg::KeyCode::e;
         case XK_f: return rg::KeyCode::f;
         case XK_g: return rg::KeyCode::g;
         case XK_h: return rg::KeyCode::h;
         case XK_i: return rg::KeyCode::i;
         case XK_j: return rg::KeyCode::j;
         case XK_k: return rg::KeyCode::k;
         case XK_l: return rg::KeyCode::l;
         case XK_m: return rg::KeyCode::m;
         case XK_n: return rg::KeyCode::n;
         case XK_o: return rg::KeyCode::o;
         case XK_p: return rg::KeyCode::p;
         case XK_q: return rg::KeyCode::q;
         case XK_r: return rg::KeyCode::r;
         case XK_s: return rg::KeyCode::s;
         case XK_t: return rg::KeyCode::t;
         case XK_u: return rg::KeyCode::u;
         case XK_v: return rg::KeyCode::v;
         case XK_w: return rg::KeyCode::w;
         case XK_x: return rg::KeyCode::x;
         case XK_y: return rg::KeyCode::y;
         case XK_z: return rg::KeyCode::z;
         case XK_braceleft: return rg::KeyCode::LeftBrace;
         case XK_bar: return rg::KeyCode::Bar;
         case XK_braceright: return rg::KeyCode::RightBrace;
         case XK_asciitilde: return rg::KeyCode::Tilde;

         default: return rg::KeyCode::Unknown;
      }

   }

}


#endif // __x11__
