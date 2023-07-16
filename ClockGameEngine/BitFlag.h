#ifndef BITFLAG_H_
#define BITFLAG_H_

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
    BitFlag& SetFlag(EventTypes flag)
    {
        m_FlagValue |= (int)flag;

        return *this;
    }

    //Sets flag to false
    BitFlag& UnsetFlag(EventTypes flag)
    {
        m_FlagValue &= ~(int)flag;

        return *this;
    }

    //Sets a flag value from true to false and vice versa
    BitFlag& FlipFlag(EventTypes flag)
    {
        m_FlagValue ^= (int)flag;

        return *this;
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

#endif