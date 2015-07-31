#pragma once

class InputEvent
{
public:
    InputEvent() {}
    virtual ~InputEvent() {}

    virtual void execute() = 0;
};