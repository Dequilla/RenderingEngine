#pragma once 
#include <cstdint>

#include "keyboard.hpp"

namespace rg
{

    enum class EventType
    {
        Close,
        FocusGain,
        FocusLost,
        Motion,
        KeyPressed,
        KeyReleased
    };

    struct MotionEvent
    {
        int64_t x;
        int64_t y;

        int64_t deltax;
        int64_t deltay;
    };

    struct KeyboardEvent
    {
        // TODO: Implement scancodes (physical device independent key presses and relases)
        KeyCode code;
        bool pressed;
    };

    class Event
    {
    public:
        EventType type;

        union {
            MotionEvent motion;
            KeyboardEvent key;
        };
    };
}
