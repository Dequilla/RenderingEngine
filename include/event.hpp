#pragma once 

namespace rg
{

    enum class EventType
    {
        Close
    };

    class Event
    {
    public:
        EventType type;
    };
}
