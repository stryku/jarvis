#pragma once

#include <InputEvent.hpp>
#include <SimpleXmlParser.hpp>

class KbEvent : public InputEvent
{
private:
    void prepareInput( InputEventType type )
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.dwFlags = getWindowsEventDwFlags( type );
    }

    static int extractKey( const std::string &eventDataInXml )
    {
        auto kbKeyStr = SimpleXmlParser::extractChildrenValue( "key", eventDataInXml.c_str() );

        return static_cast<int>( kbKeyStr[0] );
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
    ~KbEvent() {}
};