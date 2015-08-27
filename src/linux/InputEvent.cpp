#include "InputEvent.hpp"

size_t InputEvent::displayRef = 0;
Display* InputEvent::display;

void InputEvent::closeDisplay()
{
    LOG("closeDisplay() ref = "<<displayRef);
    if( display != nullptr && --displayRef == 0 )
        XCloseDisplay(display);
}

bool InputEvent::prepareDisplay()
{
    LOG("prepareDisplay() ref = "<<displayRef);
    if( displayRef++ == 0 )
    {
        display = XOpenDisplay( nullptr );

        if( display == nullptr )
            return false;
    }

    return true;
}


