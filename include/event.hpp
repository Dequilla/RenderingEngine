#pragma once 
#include <cstdint>

namespace rg
{

    enum class EventType
    {
        Close,
        Motion
    };

    struct MotionEvent
    {
        int64_t x;
        int64_t y;

        int64_t deltax;
        int64_t deltay;
    };

    class Event
    {
    public:
        EventType type;

        union {
            MotionEvent motion;
        };
    };
}
