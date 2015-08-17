#pragma once

#include "InputEvents.hpp"
#include "../SimpleXmlParser.hpp"

#include <cstdlib>

class WriteTextEvent : public AbstractEvent
{
    private:
        typedef std::shared_ptr<InputEvent> EventPtr;
        typedef std::vector<EventPtr> Events;

        Events events;

        static void insertInputsForKey( int key, Events &dest )
        {
            dest.push_back( std::make_shared<KbEvent>( KB_DOWN, key ) );
            dest.push_back( std::make_shared<KbEvent>( KB_UP, key ) );
        }

        static void str_replace( std::string &s, 
                                 const std::string &search, 
                                 const std::string &replace ) 
        {
            for( size_t pos = 0; ; pos += replace.length() ) 
            {
                pos = s.find( search, pos );
                if( pos == std::string::npos ) break;

                s.erase( pos, search.length() );
                s.insert( pos, replace );
            }
        }

        static void prepareText( std::string &text )
        {
            str_replace( text, "\\0", "<" );
            str_replace( text, "\\1", ">" );
            str_replace( text, "\\\\", "\\" );
        }

        void prepareEvents( const std::string &eventDataInXml )
        {
            auto text = SimpleXmlParser::extractChildrenValue( "text", 
                                                               eventDataInXml.c_str() );

            prepareText( text );

            for( char &key : text )
                insertInputsForKey( key, events );
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
