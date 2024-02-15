#include "system/clock.hpp"

namespace rg
{

    std::chrono::nanoseconds Duration::nanoseconds() const
    {
        return ns;
    }

    std::chrono::milliseconds Duration::milliseconds() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(ns);
    }

    std::chrono::seconds Duration::seconds() const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(ns);
    }

    std::chrono::minutes Duration::minutes() const
    {
        return std::chrono::duration_cast<std::chrono::minutes>(ns);
    }

    std::chrono::hours Duration::hours() const
    {
        return std::chrono::duration_cast<std::chrono::hours>(ns);
    }

    Duration ClockState::elapsed() const
    {
        return Duration(end - start);
    }

    TimePoint ClockState::now() const
    {
        return end;
    }

    Clock::Clock()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    ClockState Clock::now() const
    {
        return ClockState(m_start, std::chrono::high_resolution_clock::now());
    }

    ClockState Clock::restart()
    {
        ClockState state = now();
        m_start = state.now();
        return state;
    }

}
