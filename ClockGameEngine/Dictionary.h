#pragma once
#include "GameObject.h"


template <typename T, unsigned char size>
class Dictionary
{
    typedef struct Record
    {
        unsigned char id;
        T* object;
    }StackData;

public:
    Dictionary()
    {
        _stack = new StackData[size];
    }

    ~Dictionary()
    {
        delete[] _stack;
    }

    StackData& operator[](unsigned char index)
    {
        return _stack[index];
    }

    unsigned char maxSize()
    {
        return size;
    }

    unsigned char count()
    {
        return _stackCounter;
    }

    bool contains(unsigned char id)
    {
        for (int i = 0; i < size; ++i)
        {
            if (_stack[i].id == id)
                return true;
        }
        return false;
    }

    void add(unsigned char id, T* object)
    {
        if (_stackCounter >= size)
        {
            char buf[128] = { 0 };
            sprintf_s(buf, "Cannot add new object to the dictionary as maximum number of '%d' reached", size);
            throw std::exception(buf);
        }
        else
        {
            StackData tmp;
            tmp.id = id;
            tmp.object = object;
            _stack[_stackCounter] = tmp;
            _stackCounter++;
        }
    }

private:
    StackData* _stack;
    unsigned char _stackCounter = 0;

};