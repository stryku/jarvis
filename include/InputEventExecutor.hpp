#pragma once

#include <InputEvent.hpp>
#include <vector>

#include <Windows.h>

class InputEventExecutor
{
private:
    typedef std::vector<InputEvent> Events;

    struct Coordination
    {
        size_t x, y;
    };

    static void mouseSetup( INPUT &buffer )
    {
        buffer.type = INPUT_MOUSE;
        buffer.mi.dx = 0;
        buffer.mi.dy = 0;
        buffer.mi.mouseData = 0;
        buffer.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
        buffer.mi.time = 0;
        buffer.mi.dwExtraInfo = 0;
    }

    static RECT getDesktopResolution()
    {
        RECT resolution;
        const HWND hDesktop = GetDesktopWindow();

        GetWindowRect( hDesktop, &resolution );

        return resolution;
    }

    static DWORD getWindowsEventType( InputEventType eventType )
    {
        switch( eventType )
        {
            case MOUSE_LEFT_DOWN: return MOUSEEVENTF_LEFTDOWN;
            case MOUSE_LEFT_UP: return MOUSEEVENTF_LEFTUP;
            case MOUSE_RIGHT_DOWN: return MOUSEEVENTF_RIGHTDOWN;
            case MOUSE_RIGHT_UP: return MOUSEEVENTF_RIGHTUP;
            case MOUSE_MIDDLE_DOWN: return MOUSEEVENTF_MIDDLEDOWN;
            case MOUSE_MIDDLE_UP: return MOUSEEVENTF_MIDDLEUP;
            case MOUSE_X_DOWN: return MOUSEEVENTF_XDOWN;
            case MOUSE_X_UP: return MOUSEEVENTF_XUP;

            case MOUSE_MOVE: return MOUSEEVENTF_MOVE;
        }
    }

    static UINT mouseBtnEvent( InputEventType eventType )
    {
        INPUT input;
        DWORD btnEventType;

        mouseSetup( input );

        btnEventType = getWindowsEventType( eventType );

        input.mi.dwFlags = ( MOUSEEVENTF_ABSOLUTE | btnEventType );
        return SendInput( 1, &input, sizeof( INPUT ) );
    }

    static UINT mouseMove( const Point2d<size_t> &newPos )
    {
        INPUT input;
        RECT rect;

        mouseSetup( input );

        rect = getDesktopResolution();

        input.mi.dx = ( newPos.x * ( 0xFFFF / rect.right ) );
        input.mi.dy = ( newPos.y * ( 0xFFFF / rect.bottom ) );
        input.mi.dwFlags = ( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE );

        return SendInput( 1, &input, sizeof( INPUT ) );
    }

public:
    static bool execute( Events events )
    {
        for( const auto &event : events )
        {
            switch( event.type )
            {
                case MOUSE_MOVE:
                {
                    if( mouseMove( event.mouseMoveTo ) == 0 )
                        return false;
                } break;

                case MOUSE_LEFT_DOWN:
                case MOUSE_LEFT_UP:
                case MOUSE_RIGHT_DOWN:
                case MOUSE_RIGHT_UP:
                case MOUSE_MIDDLE_DOWN:
                case MOUSE_MIDDLE_UP:
                case MOUSE_X_DOWN:
                case MOUSE_X_UP:
                {
                    if( mouseBtnEvent( event.type ) == 0 )
                        return false;
                } break;
            }
        }

        return 0;
    }
};