#pragma once

#include <InputEventType.h>
#include <MouseBtnEvent.hpp>
#include <MouseMoveEvent.hpp>
#include <KbEvent.hpp>
#include <WriteTextEvent.hpp>

class EventsFactory
{
private:
    typedef std::shared_ptr<AbstractEvent> EventPtr;

public:
    static EventPtr getEvent( InputEventType type, const std::string &xmlData )
    {
        switch( type )
        {
            case MOUSE_MOVE: 
                return std::make_shared<MouseMoveEvent>( xmlData );

            case KB_DOWN:
            case KB_UP:
            return std::make_shared<KbEvent>( type, xmlData );

            case WRITE_TEXT:
                return std::make_shared<WriteTextEvent>( xmlData );

            case MOUSE_LEFT_DOWN: 
            case MOUSE_LEFT_UP: 
            case MOUSE_RIGHT_DOWN: 
            case MOUSE_RIGHT_UP: 
            case MOUSE_MIDDLE_DOWN: 
            case MOUSE_MIDDLE_UP: 
            case MOUSE_X_DOWN: 
            case MOUSE_X_UP: 
                return std::make_shared<MouseBtnEvent>( type );
        }
    }
};