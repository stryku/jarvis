#pragma once

#include "InputEvent.hpp"

class MouseBtnEvent : public InputEvent
{
private:
    void prepareInput( InputEventType type )
    {
        input.type = INPUT_MOUSE;
        input.mi.dx = 0;
        input.mi.dy = 0;
        input.mi.mouseData = 0;
        input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | getWindowsEventDwFlags( type );
        input.mi.time = 0;
        input.mi.dwExtraInfo = 0;
    }
public:
    MouseBtnEvent( InputEventType type )
    {
        prepareInput( type );
    }
    ~MouseBtnEvent() {}
};
