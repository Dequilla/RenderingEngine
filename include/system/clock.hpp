#pragma once

#include <chrono>

namespace rg
{
   
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

    struct Duration
    {
        std::chrono::nanoseconds ns;

        Duration() = default;
        Duration(std::chrono::nanoseconds ns) : ns(ns) {} 
        Duration(const Duration& d) : ns(d.ns) {}

        std::chrono::nanoseconds nanoseconds() const;
        std::chrono::milliseconds milliseconds() const; 
        std::chrono::seconds seconds() const;
        std::chrono::minutes minutes() const;
        std::chrono::hours hours() const;
    };

    struct ClockState
    {
        TimePoint start;
        TimePoint end;

        ClockState() = default;
        ClockState(TimePoint start, TimePoint end)
            : start(start), end(end) {}

        Duration elapsed() const;
        TimePoint now() const;
    };

    class Clock
    {
    protected:
        TimePoint m_start;
    
    public:
        Clock();

        ClockState now() const;
        ClockState restart();
    };

}
