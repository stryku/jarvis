#pragma once

#include <InputEvent.hpp>
#include <Point2d.hpp>
#include <SimpleXmlParser.hpp>

class MouseMoveEvent : public InputEvent
{
private:
    static Point2d<size_t> monitorRect()
    {
        RECT desktop;
        GetWindowRect( GetDesktopWindow(), &desktop );

        return { desktop.right, desktop.bottom };
    }

    static Point2d<size_t> extractData( const std::string &eventDataInXml )
    {
        Point2d<size_t> point;
        std::string strX, strY;

        strX = SimpleXmlParser::extractChildren( "x", eventDataInXml.c_str() );
        strY = SimpleXmlParser::extractChildren( "y", eventDataInXml.c_str() );

        //todo zmiana przy zmianie 
        point.x = std::atoi( strX.c_str() );
        point.y = std::atoi( strY.c_str() );

        return point;
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