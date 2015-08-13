#pragma once

#include "../AbstractEvent.hpp"
#include "SimpleXmlParser.hpp"

#include <X11/Xlib.h>
#include <X11/keysym.h>

class KbEvent : public AbstractEvent
{
    private:
        XKeyEvent event;
        Display *display = nullptr;
        Window root;
        Window winFocus;

        static int extractKey( const std::string &eventDataInXml )
        {
            auto kbKeyStr = SimpleXmlParser::extractChildrenValue( "key", eventDataInXml.c_str() );

            return static_cast<int>( kbKeyStr[0] );
        }

        static XKeyEvent createKeyEvent( Display *display, 
                Window &win,
                Window &winRoot, 
                bool press,
                int keycode, 
                int modifiers )
        {
            XKeyEvent event;

            event.display     = display;
            event.window      = win;
            event.root        = winRoot;
            event.subwindow   = None;
            event.time        = CurrentTime;
            event.x           = 1;
            event.y           = 1;
            event.x_root      = 1;
            event.y_root      = 1;
            event.same_screen = True;
            event.keycode     = XKeysymToKeycode(display, keycode);
            event.state       = modifiers;

            if(press)
                event.type = KeyPress;
            else
                event.type = KeyRelease;

            return event;
        }

        void prepareEvent( InputEventType type, int key )
        {
            int    revert;
            display = XOpenDisplay(0);

            if( display == nullptr )
                return;

            winRoot = XDefaultRootWindow(display);

            XGetInputFocus(display, &winFocus, &revert);

            event = createKeyEvent( display, 
                                    winFocus, 
                                    winRoot, 
                                    type == KB_DOWN, 
                                    key, 
                                    0);
        }

    public:
        KbEvent( InputEventType type, int key ) 
        {
            prepareInput( type );
            input.ki.wVk = key;
        }
        KbEvent( InputEventType type, const std::string &eventDataInXml )
        {
            prepareInput( type );
            input.ki.wVk = extractKey( eventDataInXml );
        }
        ~KbEvent() 
        {
            if( display != nullptr )
                XCloseDisplay(display);
        }

        bool execute()
        {
            if( display == nullptr )
                return false;

            XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

            return true;
        }
};
