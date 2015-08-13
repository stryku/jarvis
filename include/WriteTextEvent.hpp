#pragma once

#include <InputEvent.hpp>
#include <SimpleXmlParser.hpp>
#include <cstdlib>

class WriteTextEvent : public AbstractEvent
{
private:
    typedef std::shared_ptr<InputEvent> EventPtr;
    typedef std::vector<EventPtr> Events;

    Events events;

    static void insertInputsForKey( int key, Events &dest )
    {
        bool needReleaseShift = false;

        if( isupper( key ) )
        {
            needReleaseShift = true;
            dest.push_back( std::make_shared<KbEvent>( KB_DOWN, VK_SHIFT ) );
        }
        else
            key = toupper( key );

        dest.push_back( std::make_shared<KbEvent>( KB_DOWN, key ) );
        dest.push_back( std::make_shared<KbEvent>( KB_UP, key ) );

        if( needReleaseShift )
            dest.push_back( std::make_shared<KbEvent>( KB_UP, VK_SHIFT ) );
    }

    static int decodeSpecialKey( int c )
    {
        switch( c )
        {
            case '1': return '<';
            case '2': return '>';
        }
    }
    //todo
    static int getSpecialKey( char *code )
    {
        /*int intCode = std::atoi( code );

        if( isdigit( c ) )
            return decodeSpecialKey( c );

        return c;*/

        return 0;
    }

    void prepareEvents( const std::string &eventDataInXml )
    {
        auto text = SimpleXmlParser::extractChildrenValue( "text", eventDataInXml.c_str() );

        for( size_t i = 0; i < text.length(); ++i )
        {
            int key = text[i];

            if( text[i] == '\\' )
                key = getSpecialKey( &text[++i] );

            insertInputsForKey( key, events );
        }
    }

public:
    WriteTextEvent( const std::string &eventDataInXml )
    {
        prepareEvents( eventDataInXml );
    }
    ~WriteTextEvent() {}

    bool execute()
    {
        for( const auto &event : events )
            if( !event->execute() )
                return false;

        return true;
    }
};