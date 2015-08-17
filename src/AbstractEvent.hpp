#pragma once

#include "InputEventType.h"

class AbstractEvent
{
public:
    AbstractEvent() {}
    ~AbstractEvent() {}

    virtual bool execute() = 0;
};
