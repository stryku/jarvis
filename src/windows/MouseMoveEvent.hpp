#pragma once

#include "InputEvent.hpp"
#include "../Point2d.hpp"
#include "../SimpleXmlParser.hpp"

#include <windows.h>

class MouseMoveEvent : public InputEvent
{
private:
    static Point2d<size_t> monitorRect()
    {
        RECT desktop;
        GetWindowRect( GetDesktopWindow(), &desktop );

        return { desktop.right, desktop.bottom };
    }

    void prepareInput()
    {
        input.type = INPUT_MOUSE;
        input.mi.mouseData = 0;
        input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
        input.mi.time = 0;
        input.mi.dwExtraInfo = 0;
    }

    void initFromXml( const std::string &eventDataInXml )
    {
        auto newPos = extractData( eventDataInXml );
        auto displayRect = monitorRect();

        input.mi.dx = ( newPos.x * ( 0xFFFF / displayRect.x ) );
        input.mi.dy = ( newPos.y * ( 0xFFFF / displayRect.y ) );
    }

public:
    MouseMoveEvent( const std::string &eventDataInXml )
    {
        prepareInput();
        initFromXml( eventDataInXml );
    }
};
