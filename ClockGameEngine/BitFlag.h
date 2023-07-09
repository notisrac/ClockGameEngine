#pragma once
enum class EventTypes
{
    Quit = 1 << 0, // 1
    ButtonLeft = 1 << 1, // 2
    ButtonUp = 1 << 2, // 4
    ButtonDown = 1 << 3, // 8
    ButtonRight = 1 << 4, // 16
    ButtonReturn = 1 << 5, // 32
    ButtonSpace = 1 << 6, // 64
    //Flag8 = 1 << 7  // 128
};

struct BitFlag
{
    void Clear()
    {
        m_FlagValue = 0;
    }

    //Sets flag to true
    void SetFlag(EventTypes flag)
    {
        m_FlagValue |= (int)flag;
    }

    //Sets flag to false
    void UnsetFlag(EventTypes flag)
    {
        m_FlagValue &= ~(int)flag;
    }

    //Sets a flag value from true to false and vice versa
    void FlipFlag(EventTypes flag)
    {
        m_FlagValue ^= (int)flag;
    }

    //Check whether a flag is set to true
    bool HasFlag(EventTypes flag)
    {
        return (m_FlagValue & (int)flag) == (int)flag;
    }

    bool HasAnyFlag(EventTypes multiFlag)
    {
        return (m_FlagValue & (int)multiFlag) != 0;
    }

    int m_FlagValue = 0;
};
