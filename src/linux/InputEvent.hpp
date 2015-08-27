#pragma once

#include "../AbstractEvent.hpp"
#include "../log.h"

#include <X11/Xlib.h>

#include <unistd.h>
#include <cstring>

class InputEvent : public AbstractEvent
{
    private:
        static size_t displayRef;

    protected:
        XEvent event;
        static Display *display;
        InputEventType type;

        enum ButtonDirection
        {
            DOWN,
            UP,
            UNKNOW
        };

        static ButtonDirection buttonDirection( InputEventType type )
        {
            switch( type )
            {
                case MOUSE_LEFT_UP:
                case MOUSE_RIGHT_UP:
                case MOUSE_MIDDLE_UP:
                case KB_UP:
                    return UP;

                case MOUSE_LEFT_DOWN:
                case MOUSE_RIGHT_DOWN:
                case MOUSE_MIDDLE_DOWN:
                case KB_DOWN:
                    return DOWN;

                default: 
                    return UNKNOW;
            }
        }
        void closeDisplay();

        bool prepareDisplay();

        virtual bool prepare()
        {
            return prepareDisplay();
        }

    public:
        InputEvent( InputEventType type ) :
            type( type )
    {
        prepareDisplay();
    }
        virtual ~InputEvent() 
        {
            closeDisplay();
        }
};

