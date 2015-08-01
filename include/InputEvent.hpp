#pragma once

#include <InputEventType.h>
#include <Point.hpp>

struct InputEvent
{
    InputEventType type;
    union
    {
        int kbKey;
        Point2d<size_t> mouseMoveTo;
    };
};