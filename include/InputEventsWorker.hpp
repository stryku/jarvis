#pragma once

#include <Worker.hpp>
#include <SimpleXmlParser.hpp>
#include <log.h>
#include <InputEventsWorkerResult.hpp> // TODO
#include <InputEvent.hpp>
#include <mutex>

class InputEventsWorker : public Worker //todo
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        //todo
    }workData;

    InputEventType stringToEnumType( const std::string &stringType )
    {
        static std::map<const std::string&, InputEventType> map{
            { "MOUSE_LEFT_DOWN", MOUSE_LEFT_DOWN },
            { "MOUSE_LEFT_UP", MOUSE_LEFT_UP },
            { "MOUSE_RIGHT_DOWN", MOUSE_RIGHT_DOWN },
            { "MOUSE_RIGHT_UP", MOUSE_RIGHT_UP },
            { "MOUSE_MIDDLE_DOWN", MOUSE_MIDDLE_DOWN },
            { "MOUSE_MIDDLE_UP", MOUSE_MIDDLE_UP },
            { "MOUSE_X_DOWN", MOUSE_X_DOWN },
            { "MOUSE_X_UP", MOUSE_X_UP },
            { "MOUSE_SCROLL_DOWN", MOUSE_SCROLL_DOWN },
            { "MOUSE_SCROLL_UP", MOUSE_SCROLL_UP },
            { "MOUSE_MOVE", MOUSE_MOVE }
        };

        return map[stringType];
    }

    InputEventType extractType( const std::string &eventInXml )
    {
        auto stringType = SimpleXmlParser::extractChildren( "type", eventInXml.c_str() );

        return stringToEnumType( stringType );
    }



    void extractWorkData( const char *taskData )
    {
        //todo

        /*auto data = SimpleXmlParser::extractChildren( "path", taskData );
        */
    }

public:
    InputEventsWorker() {}
    ~InputEventsWorker() {}

    WorkerResultPtr doWork( const char *data )
    {
        try
        {
            std::string taskData( data );

            extractWorkData( taskData.c_str() );

            //todo
            LOG( "" );

            //todo do work methods

            return std::make_shared<InputEventsWorkerResult>( RC_SUCCESS );//todo
        }
        catch( ... )
        {
            return std::make_shared<InputEventsWorkerResult>( RC_FAIL );//todo
        }

        return std::make_shared<InputEventsWorkerResult>( RC_FAIL );//todo
    }
};