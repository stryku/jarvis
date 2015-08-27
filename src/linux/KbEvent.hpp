#pragma once

#include "InputEvent.hpp"
#include "../InputEventDataExtractor.hpp"
#include "log.h";

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <cctype>
#include <thread>
#include <chrono>

class KbEvent : public InputEvent
{
    private:
        typedef InputEventDataExtractor DataExtractor;

        XKeyEvent event;
        Window root;
        Window winFocus;
        int mask;
        int key;

        static int getXEventMask( InputEventType type )
        {
            switch( buttonDirection( type ) )
            {
                case UP: return KeyPressMask;
                case DOWN: return KeyReleaseMask;

                default: return -1;
            }
        }


        static int getXEventType( InputEventType type )
        {
            switch( buttonDirection( type ) )
            {
                case UP: return KeyPress;
                case DOWN: return KeyRelease;

                default: return -1;
            }
        }

        static bool needShift( const char c )
        {
            static const std::string charsThatNeedShift = "QWERTYUIOPASDFGHJKLZXCVBNM~!@#$%^&*()_+{}|:\"<>?";

            return charsThatNeedShift.find( c ) != std::string::npos;
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
            event.send_event  = true;

            if( needShift( keycode ) && press )
                event.state |= XK_Shift_L;

            return event;
        }

        void init()
        {
            int revert;

            root = XDefaultRootWindow(display);

            XGetInputFocus(display, &winFocus, &revert);


            event = createKeyEvent( display, 
                    winFocus, 
                    root,
                    getXEventType( type ) == KeyPress,
                    key, 
                    0 );

            event.type = getXEventType( type );
        }

        bool prepare()
        {
            if( display == nullptr )
                return false;

            init();

            return true;
        }


    public:
        KbEvent( InputEventType type, int key ) :
            InputEvent( type ),
            key( key )
    {
    }
        KbEvent( InputEventType type, const std::string &eventDataInXml ) :
            InputEvent( type )
            {
                key = DataExtractor::kbKey( eventDataInXml );
            }
        ~KbEvent() 
        {
        }

        bool execute()
        {
            if( !prepare() )
            {
                return false;
            }

            LOG("executing: "<<(char)key<<" "<<key<<", " <<event.keycode);

            int result = XSendEvent( event.display, 
                    event.window, 
                    True, 
                    mask, 
                    reinterpret_cast<XEvent*>( &event ) );

            std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

            return result != 0;
        }
};
