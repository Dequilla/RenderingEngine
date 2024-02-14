#pragma once

#ifdef __x11__
#include "platform/x11/x11_keyboard.hpp"
#else
#pragma message "No keyboard supported for selected plattform. X11 supported."
#endif


