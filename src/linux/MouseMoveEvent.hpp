#pragma once

#include "InputEvent.hpp"
#include "../InputEventDataExtractor.hpp"

class MouseMoveEvent : public InputEvent
{
    private:
        typedef InputEventDataExtractor DataExtractor;

        Point2d<size_t> newCoord;

        Point2d<size_t> currentCoord()
        {
            if( display == nullptr )
                return Point2d<size_t>();

            XQueryPointer( display, 
                           DefaultRootWindow (display),
                           &event.xbutton.root, 
                           &event.xbutton.window,
                           &event.xbutton.x_root, 
                           &event.xbutton.y_root,
                           &event.xbutton.x, 
                           &event.xbutton.y,
                           &event.xbutton.state );

            return { static_cast<size_t>( event.xbutton.x ), 
                     static_cast<size_t>( event.xbutton.y ) };
        }

    public:
        MouseMoveEvent( const std::string &eventDataInXml ) :
            InputEvent( MOUSE_MOVE )
        {
            newCoord = DataExtractor::newMouseCoord( eventDataInXml );
        }

        bool execute()
        {
            if( !prepare() )
                return false;

            auto current = currentCoord();

            XWarpPointer( display, None, None, 0,0,0,0, 
                          -current.x, 
                          -current.y );

            XWarpPointer( display, None, None, 0,0,0,0, 
                          newCoord.x, 
                          newCoord.y );

            XFlush( display );
            usleep( 1 );

            closeDisplay();

            return true;
        }
};
