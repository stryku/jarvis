#include <InputEventTypeMap.hpp>

void InputEventTypeMap::init()
{
    add( "MOUSE_LEFT_DOWN", MOUSE_LEFT_DOWN );
    add( "MOUSE_LEFT_UP", MOUSE_LEFT_UP );
    add( "MOUSE_RIGHT_DOWN", MOUSE_RIGHT_DOWN );
    add( "MOUSE_RIGHT_UP", MOUSE_RIGHT_UP );
    add( "MOUSE_MIDDLE_DOWN", MOUSE_MIDDLE_DOWN );
    add( "MOUSE_MIDDLE_UP", MOUSE_MIDDLE_UP );
    add( "MOUSE_X_DOWN", MOUSE_X_DOWN );
    add( "MOUSE_X_UP", MOUSE_X_UP );
    add( "MOUSE_SCROLL_DOWN", MOUSE_SCROLL_DOWN );
    add( "MOUSE_SCROLL_UP", MOUSE_SCROLL_UP );
    add( "MOUSE_MOVE", MOUSE_MOVE );
    add( "KB_UP", KB_UP );
    add( "KB_DOWN", KB_DOWN );
    add( "WRITE_TEXT", WRITE_TEXT );
}
