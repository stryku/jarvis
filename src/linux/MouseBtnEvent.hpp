#pragma once

#include "InputEvent.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>


class MouseBtnEvent : public InputEvent
{
    private:
        int mask;
        
        static int toButton( InputEventType type )
        {
            switch( type )
            {
                case MOUSE_LEFT_UP:
                case MOUSE_LEFT_DOWN:
                    return Button1;

                case MOUSE_RIGHT_UP:
                case MOUSE_RIGHT_DOWN:
                    return Button3;

                case MOUSE_MIDDLE_UP:
                case MOUSE_MIDDLE_DOWN:
                    return Button2;

                default:
                    return -1;
            }
        }

        static int getXEventType( InputEventType type )
        {
            switch( buttonDirection( type ) )
            {
                case UP: return ButtonPress;
                case DOWN: return ButtonRelease;

                default: return -1;
            }
        }

        static int getXEventMask( InputEventType type )
        {
            switch( buttonDirection( type ) )
            {
                case UP: return ButtonPressMask;
                case DOWN: return ButtonReleaseMask;

                default: return -1;
            }
        }

        void init()
        {
            std::memset ( &event, 0, sizeof( event ) );

            event.xbutton.button = toButton( type );
            event.xbutton.same_screen = True;
            event.xbutton.subwindow = DefaultRootWindow ( display );
            event.type = getXEventType( type );

            while( event.xbutton.subwindow )
            {
                event.xbutton.window = event.xbutton.subwindow;

                XQueryPointer ( display, 
                                event.xbutton.window,
                                &event.xbutton.root, 
                                &event.xbutton.subwindow,
                                &event.xbutton.x_root, 
                                &event.xbutton.y_root,
                                &event.xbutton.x, 
                                &event.xbutton.y,
                                &event.xbutton.state );
            }

            mask = getXEventMask( type );
        }

        bool prepare()
        {
            if( !prepareDisplay() )
                return false;

            init();

            return true;
        }

    public:
        MouseBtnEvent( InputEventType type ) :
            InputEvent( type )
        {
        }
        ~MouseBtnEvent() {}

        bool execute()
        {
            if( !prepare() )
                return false;

            auto result = XSendEvent( display, 
                                      PointerWindow,
                                      True, 
                                      mask,
                                      &event );

            if ( result == 0 )
            {
                closeDisplay();
                return false;
            }

            XFlush( display );
            usleep( 1 );

            closeDisplay();

            return true;
        }
};
