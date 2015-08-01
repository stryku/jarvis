#pragma once

class AbstractEvent
{
public:
    AbstractEvent() {}
    ~AbstractEvent() {}

    virtual bool execute() = 0;
};