#pragma once

#include <InputEventType.h>
#include <AbstractEvent.hpp>

#include <string>

#include <windows.h>

class InputEvent : public AbstractEvent
{
protected:
    INPUT input;

    static DWORD getWindowsEventDwFlags( InputEventType eventType )
    {
        switch( eventType )
        {
            case MOUSE_LEFT_DOWN: return MOUSEEVENTF_LEFTDOWN;
            case MOUSE_LEFT_UP: return MOUSEEVENTF_LEFTUP;
            case MOUSE_RIGHT_DOWN: return MOUSEEVENTF_RIGHTDOWN;
            case MOUSE_RIGHT_UP: return MOUSEEVENTF_RIGHTUP;
            case MOUSE_MIDDLE_DOWN: return MOUSEEVENTF_MIDDLEDOWN;
            case MOUSE_MIDDLE_UP: return MOUSEEVENTF_MIDDLEUP;
            case MOUSE_X_DOWN: return MOUSEEVENTF_XDOWN;
            case MOUSE_X_UP: return MOUSEEVENTF_XUP;

            case MOUSE_MOVE: return MOUSEEVENTF_MOVE;

            case KB_DOWN: return 0;
            case KB_UP: return KEYEVENTF_KEYUP;
        }
    }

public:
    InputEvent() {}
    virtual ~InputEvent() {}

    virtual bool execute()
    {
        return SendInput( 1, &input, sizeof( INPUT ) ) != 0;
    }
};