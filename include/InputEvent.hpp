#pragma once

#include <InputEventType.h>
#include <Point2d.hpp>

struct InputEvent
{
    InputEventType type;
    union
    {
        int kbKey;
        Point2d<size_t> mouseMoveTo;
    };

    bool isEventWithData() const
    {
        return type == MOUSE_MOVE ||
               type == KB_DOWN ||
               type == KB_UP;
    }
};