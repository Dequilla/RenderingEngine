// Source: https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
// Modified to use enum class and not fully implemented.

/* $Xorg: keysymdef.h,v 1.4 2001/02/09 02:03:23 $ */

/***********************************************************
Copyright 1987, 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $XFree86: $ */

/*
 * The "X11 Window System Protocol" standard defines in Appendix A the
 * keysym codes. These 29-bit integer values identify characters or
 * functions associated with each key (e.g., via the visible
 * engraving) of a keyboard layout. This file assigns mnemonic macro
 * names for these keysyms.
 *
 * This file is also compiled (by xc/lib/X11/util/makekeys.c) into
 * hash tables that can be accessed with X11 library functions such as
 * XStringToKeysym() and XKeysymToString().
 *
 * Where a keysym corresponds one-to-one to an ISO 10646 / Unicode
 * character, this is noted in a comment that provides both the U+xxxx
 * Unicode position, as well as the official Unicode name of the
 * character.
 *
 * Where the correspondence is either not one-to-one or semantically
 * unclear, the Unicode position and name are enclosed in
 * parentheses. Such legacy keysyms should be considered deprecated
 * and are not recommended for use in future keyboard mappings.
 *
 * For any future extension of the keysyms with characters already
 * found in ISO 10646 / Unicode, the following algorithm shall be
 * used. The new keysym code position will simply be the character's
 * Unicode number plus 0x01000000. The keysym values in the range
 * 0x01000100 to 0x0110ffff are reserved to represent Unicode
 * characters in the range U+0100 to U+10FFFF.
 *
 * While most newer Unicode-based X11 clients do already accept
 * Unicode-mapped keysyms in the range 0x01000100 to 0x0110ffff, it
 * will remain necessary for clients -- in the interest of
 * compatibility with existing servers -- to also understand the
 * existing legacy keysym values in the range 0x0100 to 0x20ff.
 *
 * Where several mnemonic names are defined for the same keysym in this
 * file, all but the first one listed should be considered deprecated.
 *
 * Mnemonic names for keysyms are defined in this file with lines
 * that match one of these Perl regular expressions:
 *
 *    /^\#define XK_([a-zA-Z_0-9]+)\s+0x([0-9a-f]+)\s*\/\* U+([0-9A-F]{4,6}) (.*) \*\/\s*$/
 *    /^\#define XK_([a-zA-Z_0-9]+)\s+0x([0-9a-f]+)\s*\/\*\(U+([0-9A-F]{4,6}) (.*)\)\*\/\s*$/
 *    /^\#define XK_([a-zA-Z_0-9]+)\s+0x([0-9a-f]+)\s*(\/\*\s*(.*)\s*\*\/)?\s*$/
 *
 * When adding new keysyms to this file, do not forget to also update the
 * mappings in xc/lib/X11/KeyBind.c and the protocol specification in
 * xc/doc/specs/XProtocol/X11.keysyms.
 */

#pragma once

#ifdef __x11__

namespace rg
{

   enum class KeyCode
   {
      // Keypad
      KP_Space     = 0xff80,
      KP_Tab       = 0xff89,
      KP_Enter     = 0xff8d,
      KP_F1        = 0xff91,
      KP_F2        = 0xff92,
      KP_F3        = 0xff93,
      KP_F4        = 0xff94,
      KP_Home      = 0xff95,
      KP_Left      = 0xff96,
      KP_Up        = 0xff97,
      KP_Right     = 0xff98,
      KP_Down      = 0xff99,
      KP_Prior     = 0xff9a,
      KP_PageUp    = 0xff9a,
      KP_Next      = 0xff9b,
      KP_PageDown  = 0xff9b,
      KP_End       = 0xff9c,
      KP_Begin     = 0xff9d,
      KP_Insert    = 0xff9e,
      KP_Delete    = 0xff9f,
      KP_Equal     = 0xffbd,
      KP_Multiply  = 0xffaa,
      KP_Add       = 0xffab,
      KP_Separator = 0xffac,
      KP_Subtract  = 0xffad,
      KP_Decimal   = 0xffae,
      KP_Divide    = 0xffaf,

      KP_0 = 0xffb0,
      KP_1 = 0xffb1,
      KP_2 = 0xffb2,
      KP_3 = 0xffb3,
      KP_4 = 0xffb4,
      KP_5 = 0xffb5,
      KP_6 = 0xffb6,
      KP_7 = 0xffb7,
      KP_8 = 0xffb8,
      KP_9 = 0xffb9,

      // Function keys
      F1  =  0xffbe,
      F2  =  0xffbf,
      F3  =  0xffc0,
      F4  =  0xffc1,
      F5  =  0xffc2,
      F6  =  0xffc3,
      F7  =  0xffc4,
      F8  =  0xffc5,
      F9  =  0xffc6,
      F10 =  0xffc7,
      F11 =  0xffc8,
      L1  =  0xffc8,
      F12 =  0xffc9,
      L2  =  0xffc9,
      F13 =  0xffca,
      L3  =  0xffca,
      F14 =  0xffcb,
      L4  =  0xffcb,
      F15 =  0xffcc,
      L5  =  0xffcc,
      F16 =  0xffcd,
      L6  =  0xffcd,
      F17 =  0xffce,
      L7  =  0xffce,
      F18 =  0xffcf,
      L8  =  0xffcf,
      F19 =  0xffd0,
      L9  =  0xffd0,
      F20 =  0xffd1,
      L10 =  0xffd1,
      F21 =  0xffd2,
      R1  =  0xffd2,
      F22 =  0xffd3,
      R2  =  0xffd3,
      F23 =  0xffd4,
      R3  =  0xffd4,
      F24 =  0xffd5,
      R4  =  0xffd5,
      F25 =  0xffd6,
      R5  =  0xffd6,
      F26 =  0xffd7,
      R6  =  0xffd7,
      F27 =  0xffd8,
      R7  =  0xffd8,
      F28 =  0xffd9,
      R8  =  0xffd9,
      F29 =  0xffda,
      R9  =  0xffda,
      F30 =  0xffdb,
      R10 =  0xffdb,
      F31 =  0xffdc,
      R11 =  0xffdc,
      F32 =  0xffdd,
      R12 =  0xffdd,
      F33 =  0xffde,
      R13 =  0xffde,
      F34 =  0xffdf,
      R14 =  0xffdf,
      F35 =  0xffe0,
      R15 =  0xffe0,

      // Modifiers
      LeftShift      = 0xffe1,  /* Left shift */
      RightShift     = 0xffe2,  /* Right shift */
      LeftControl    = 0xffe3,  /* Left control */
      RightControl   = 0xffe4,  /* Right control */
      CapsLock       = 0xffe5,  /* Caps lock */
      ShiftLock      = 0xffe6,  /* Shift lock */
      
      LeftMeta    = 0xffe7,  /* Left meta */
      RightMeta   = 0xffe8,  /* Right meta */
      LeftAlt     = 0xffe9,  /* Left alt */
      RightAlt    = 0xffea,  /* Right alt */
      LeftSuper   = 0xffeb,  /* Left super */
      RightSuper  = 0xffec,  /* Right super */
      LeftHyper   = 0xffed,  /* Left hyper */
      RightHyper  = 0xffee,  /* Right hyper */

      // Latin 1
      Space             = 0x0020,  /* U+0020 SPACE */
      Exclam            = 0x0021,  /* U+0021 EXCLAMATION MARK */
      Quotedbl          = 0x0022,  /* U+0022 QUOTATION MARK */
      Numbersign        = 0x0023,  /* U+0023 NUMBER SIGN */
      Dollar            = 0x0024,  /* U+0024 DOLLAR SIGN */
      Percent           = 0x0025,  /* U+0025 PERCENT SIGN */
      Ampersand         = 0x0026,  /* U+0026 AMPERSAND */
      Apostrophe        = 0x0027,  /* U+0027 APOSTROPHE */
      LeftParen         = 0x0028,  /* U+0028 LEFT PARENTHESIS */
      RightParen        = 0x0029,  /* U+0029 RIGHT PARENTHESIS */
      Asterisk          = 0x002a,  /* U+002A ASTERISK */
      Plus              = 0x002b,  /* U+002B PLUS SIGN */
      Comma             = 0x002c,  /* U+002C COMMA */
      Minus             = 0x002d,  /* U+002D HYPHEN-MINUS */
      period            = 0x002e,  /* U+002E FULL STOP */
      Slash             = 0x002f,  /* U+002F SOLIDUS */
      Num0              = 0x0030,  /* U+0030 DIGIT ZERO */
      Num1              = 0x0031,  /* U+0031 DIGIT ONE */
      Num2              = 0x0032,  /* U+0032 DIGIT TWO */
      Num3              = 0x0033,  /* U+0033 DIGIT THREE */
      Num4              = 0x0034,  /* U+0034 DIGIT FOUR */
      Num5              = 0x0035,  /* U+0035 DIGIT FIVE */
      Num6              = 0x0036,  /* U+0036 DIGIT SIX */
      Num7              = 0x0037,  /* U+0037 DIGIT SEVEN */
      Num8              = 0x0038,  /* U+0038 DIGIT EIGHT */
      Num9              = 0x0039,  /* U+0039 DIGIT NINE */
      Colon             = 0x003a,  /* U+003A COLON */
      Semicolon         = 0x003b,  /* U+003B SEMICOLON */
      Less              = 0x003c,  /* U+003C LESS-THAN SIGN */
      Equal             = 0x003d,  /* U+003D EQUALS SIGN */
      Greater           = 0x003e,  /* U+003E GREATER-THAN SIGN */
      Question          = 0x003f,  /* U+003F QUESTION MARK */
      At                = 0x0040,  /* U+0040 COMMERCIAL AT */
      A                 = 0x0041,  /* U+0041 LATIN CAPITAL LETTER A */
      B                 = 0x0042,  /* U+0042 LATIN CAPITAL LETTER B */
      C                 = 0x0043,  /* U+0043 LATIN CAPITAL LETTER C */
      D                 = 0x0044,  /* U+0044 LATIN CAPITAL LETTER D */
      E                 = 0x0045,  /* U+0045 LATIN CAPITAL LETTER E */
      F                 = 0x0046,  /* U+0046 LATIN CAPITAL LETTER F */
      G                 = 0x0047,  /* U+0047 LATIN CAPITAL LETTER G */
      H                 = 0x0048,  /* U+0048 LATIN CAPITAL LETTER H */
      I                 = 0x0049,  /* U+0049 LATIN CAPITAL LETTER I */
      J                 = 0x004a,  /* U+004A LATIN CAPITAL LETTER J */
      K                 = 0x004b,  /* U+004B LATIN CAPITAL LETTER K */
      L                 = 0x004c,  /* U+004C LATIN CAPITAL LETTER L */
      M                 = 0x004d,  /* U+004D LATIN CAPITAL LETTER M */
      N                 = 0x004e,  /* U+004E LATIN CAPITAL LETTER N */
      O                 = 0x004f,  /* U+004F LATIN CAPITAL LETTER O */
      P                 = 0x0050,  /* U+0050 LATIN CAPITAL LETTER P */
      Q                 = 0x0051,  /* U+0051 LATIN CAPITAL LETTER Q */
      R                 = 0x0052,  /* U+0052 LATIN CAPITAL LETTER R */
      S                 = 0x0053,  /* U+0053 LATIN CAPITAL LETTER S */
      T                 = 0x0054,  /* U+0054 LATIN CAPITAL LETTER T */
      U                 = 0x0055,  /* U+0055 LATIN CAPITAL LETTER U */
      V                 = 0x0056,  /* U+0056 LATIN CAPITAL LETTER V */
      W                 = 0x0057,  /* U+0057 LATIN CAPITAL LETTER W */
      X                 = 0x0058,  /* U+0058 LATIN CAPITAL LETTER X */
      Y                 = 0x0059,  /* U+0059 LATIN CAPITAL LETTER Y */
      Z                 = 0x005a,  /* U+005A LATIN CAPITAL LETTER Z */
      LeftBracket       = 0x005b,  /* U+005B LEFT SQUARE BRACKET */
      Backslash         = 0x005c,  /* U+005C REVERSE SOLIDUS */
      RightBracket      = 0x005d,  /* U+005D RIGHT SQUARE BRACKET */
      Asciicircum       = 0x005e,  /* U+005E CIRCUMFLEX ACCENT */
      Underscore        = 0x005f,  /* U+005F LOW LINE */
      Grave             = 0x0060,  /* U+0060 GRAVE ACCENT */
      a                 = 0x0061,  /* U+0061 LATIN SMALL LETTER A */
      b                 = 0x0062,  /* U+0062 LATIN SMALL LETTER B */
      c                 = 0x0063,  /* U+0063 LATIN SMALL LETTER C */
      d                 = 0x0064,  /* U+0064 LATIN SMALL LETTER D */
      e                 = 0x0065,  /* U+0065 LATIN SMALL LETTER E */
      f                 = 0x0066,  /* U+0066 LATIN SMALL LETTER F */
      g                 = 0x0067,  /* U+0067 LATIN SMALL LETTER G */
      h                 = 0x0068,  /* U+0068 LATIN SMALL LETTER H */
      i                 = 0x0069,  /* U+0069 LATIN SMALL LETTER I */
      j                 = 0x006a,  /* U+006A LATIN SMALL LETTER J */
      k                 = 0x006b,  /* U+006B LATIN SMALL LETTER K */
      l                 = 0x006c,  /* U+006C LATIN SMALL LETTER L */
      m                 = 0x006d,  /* U+006D LATIN SMALL LETTER M */
      n                 = 0x006e,  /* U+006E LATIN SMALL LETTER N */
      o                 = 0x006f,  /* U+006F LATIN SMALL LETTER O */
      p                 = 0x0070,  /* U+0070 LATIN SMALL LETTER P */
      q                 = 0x0071,  /* U+0071 LATIN SMALL LETTER Q */
      r                 = 0x0072,  /* U+0072 LATIN SMALL LETTER R */
      s                 = 0x0073,  /* U+0073 LATIN SMALL LETTER S */
      t                 = 0x0074,  /* U+0074 LATIN SMALL LETTER T */
      u                 = 0x0075,  /* U+0075 LATIN SMALL LETTER U */
      v                 = 0x0076,  /* U+0076 LATIN SMALL LETTER V */
      w                 = 0x0077,  /* U+0077 LATIN SMALL LETTER W */
      x                 = 0x0078,  /* U+0078 LATIN SMALL LETTER X */
      y                 = 0x0079,  /* U+0079 LATIN SMALL LETTER Y */
      z                 = 0x007a,  /* U+007A LATIN SMALL LETTER Z */
      LeftBrace         = 0x007b,  /* U+007B LEFT CURLY BRACKET */
      Bar               = 0x007c,  /* U+007C VERTICAL LINE */
      RightBrace        = 0x007d,  /* U+007D RIGHT CURLY BRACKET */
      Tilde             = 0x007e,  /* U+007E TILDE */
      
      NoBreakSpace      = 0x00a0,  /* U+00A0 NO-BREAK SPACE */
      ExclamDown        = 0x00a1,  /* U+00A1 INVERTED EXCLAMATION MARK */
      Cent              = 0x00a2,  /* U+00A2 CENT SIGN */
      Sterling          = 0x00a3,  /* U+00A3 POUND SIGN */
      Currency          = 0x00a4,  /* U+00A4 CURRENCY SIGN */
      Yen               = 0x00a5,  /* U+00A5 YEN SIGN */
      BrokenBar         = 0x00a6,  /* U+00A6 BROKEN BAR */
      Section           = 0x00a7,  /* U+00A7 SECTION SIGN */
      Diaeresis         = 0x00a8,  /* U+00A8 DIAERESIS */
      Copyright         = 0x00a9,  /* U+00A9 COPYRIGHT SIGN */
      Ordfeminine       = 0x00aa,  /* U+00AA FEMININE ORDINAL INDICATOR */
      LeftGuillemot     = 0x00ab,  /* U+00AB LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
      NotSign           = 0x00ac,  /* U+00AC NOT SIGN */
      Hyphen            = 0x00ad,  /* U+00AD SOFT HYPHEN */
      Registered        = 0x00ae,  /* U+00AE REGISTERED SIGN */
      Macron            = 0x00af,  /* U+00AF MACRON */
      Degree            = 0x00b0,  /* U+00B0 DEGREE SIGN */
      PlusMinus         = 0x00b1,  /* U+00B1 PLUS-MINUS SIGN */
      TwoSuperior       = 0x00b2,  /* U+00B2 SUPERSCRIPT TWO */
      ThreeSuperior     = 0x00b3,  /* U+00B3 SUPERSCRIPT THREE */
      Acute             = 0x00b4,  /* U+00B4 ACUTE ACCENT */
      Mu                = 0x00b5,  /* U+00B5 MICRO SIGN */
      Paragraph         = 0x00b6,  /* U+00B6 PILCROW SIGN */
      PeriodCentered    = 0x00b7,  /* U+00B7 MIDDLE DOT */
      Cedilla           = 0x00b8,  /* U+00B8 CEDILLA */
      OneSuperior       = 0x00b9,  /* U+00B9 SUPERSCRIPT ONE */
      Masculine         = 0x00ba,  /* U+00BA MASCULINE ORDINAL INDICATOR */
      RightGuillemot    = 0x00bb,  /* U+00BB RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
      OneQuarter        = 0x00bc,  /* U+00BC VULGAR FRACTION ONE QUARTER */
      OneHalf           = 0x00bd,  /* U+00BD VULGAR FRACTION ONE HALF */
      ThreeQuarters     = 0x00be,  /* U+00BE VULGAR FRACTION THREE QUARTERS */
      QuestionDown      = 0x00bf,  /* U+00BF INVERTED QUESTION MARK */
   };

}


#endif // __x11__
