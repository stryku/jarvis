#pragma once

#include <Worker.hpp>
#include <SimpleXmlParser.hpp>
#include <log.h>
#include <SimpleWorkerResult.hpp> // TODO
#include <InputEvent.hpp>
#include <InputEventExecutor.hpp>
#include <InputEventTypeMap.hpp>

#include <string>
#include <mutex>

class InputEventsWorker : public Worker //todo
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    static InputEventTypeMap eventTypeMap;

    struct WorkData
    {
        std::vector<InputEvent> eventsToExecute;
    }workData;

    static InputEventType extractType( const std::string &eventInXml )
    {
        auto stringType = SimpleXmlParser::extractChildren( "type", eventInXml.c_str() );

        return eventTypeMap[stringType];
    }

    static Point2d<size_t> extractMouseMoveData( const std::string &eventDataInXml )
    {
        Point2d<size_t> point;
        std::string strX, strY;

        strX = SimpleXmlParser::extractChildren( "x", eventDataInXml.c_str() );
        strY = SimpleXmlParser::extractChildren( "y", eventDataInXml.c_str() );

        //todo zmiana przy zmianie 
        point.x = std::atoi( strX.c_str() );
        point.y = std::atoi( strY.c_str() );

        return point;
    }

    static int extractKbKeyData( const std::string &eventDataInXml )
    {
        auto kbKeyStr = SimpleXmlParser::extractChildrenValue( "key", eventDataInXml.c_str() );

        return static_cast<int>( kbKeyStr[0] );
    }

    static void extractData( const std::string &eventInXml, InputEvent &event )
    {
        auto eventData = SimpleXmlParser::wholeChildrenValue( "data", 
                                                              eventInXml.c_str() );

        if( event.type == MOUSE_MOVE )
            event.mouseMoveTo = extractMouseMoveData( eventData );
        else
            event.kbKey = extractKbKeyData( eventData );
    }

    static InputEvent extractEvent( const std::string &eventInXml )
    {
        InputEvent event;

        event.type = extractType( eventInXml );

        if( event.isEventWithData() )
            extractData( eventInXml, event );

        return event;
    }

    void extractWorkData( const char *taskData )
    {
        auto childrens = SimpleXmlParser::extractChildrens( "event", taskData );

        std::transform( childrens.begin(),
                        childrens.end(),
                        std::back_inserter( workData.eventsToExecute ),
                        extractEvent );
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
            LOG( "InputEventsWorker::doWork" );

            if( !InputEventExecutor::execute( workData.eventsToExecute ) )
                throw std::runtime_error( "InputEventExecutor::execute return false" );

            return std::make_shared<SimpleWorkerResult>( RC_SUCCESS );//todo
        }
        catch( ... )
        {
            return std::make_shared<SimpleWorkerResult>( RC_FAIL );//todo
        }

        return std::make_shared<SimpleWorkerResult>( RC_FAIL );//todo
    }
};

