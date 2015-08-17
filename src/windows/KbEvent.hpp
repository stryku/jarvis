#pragma once

#include "InputEvent.hpp"
#include "../InputEventDataExtractor.hpp"

class KbEvent : public InputEvent
{
private:
    typedef InputEventDataExtractor DataExtractor;

    void prepareInput( InputEventType type )
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.dwFlags = getWindowsEventDwFlags( type );
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
        input.ki.wVk = DataExtractor::extractKbKey( eventDataInXml );
    }
    ~KbEvent() {}
};
