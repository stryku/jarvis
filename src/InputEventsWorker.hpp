#pragma once

#include "Worker.hpp"
#include "SimpleXmlParser.hpp"
#include "log.h"
#include "SimpleWorkerResult.hpp"

#ifdef WIN32
#include "windows/EventsFactory.hpp"
#endif

#ifdef __linux__
#include "linux/EventsFactory.hpp"
#endif

#include <string>
#include <mutex>
#include <thread>

class InputEventsWorker : public Worker
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;
    typedef std::shared_ptr<AbstractEvent> AbstractEventPtr;
    typedef std::uniqie_ptr<AbstractEventFactory> EventsFactoryPtr;
    
    static const size_t defSleepTime = 2000;

    static InputEventTypeMap eventTypeMap;
    static EventsFactoryPtr eventsFactory;

    struct WorkData
    {
        std::vector<AbstractEventPtr> eventsToExecute;
    }workData;

    static InputEventType extractType( const std::string &eventInXml )
    {
        auto stringType = SimpleXmlParser::extractChildren( "type", eventInXml.c_str() );

        return eventTypeMap[stringType];
    }

    //static Point2d<size_t> extractMouseMoveData( const std::string &eventDataInXml )
    //{
    //    Point2d<size_t> point;
    //    std::string strX, strY;

    //    strX = SimpleXmlParser::extractChildren( "x", eventDataInXml.c_str() );
    //    strY = SimpleXmlParser::extractChildren( "y", eventDataInXml.c_str() );

    //    //todo zmiana przy zmianie 
    //    point.x = std::atoi( strX.c_str() );
    //    point.y = std::atoi( strY.c_str() );

    //    return point;
    //}

    //static int extractKbKeyData( const std::string &eventDataInXml )
    //{
    //    auto kbKeyStr = SimpleXmlParser::extractChildrenValue( "key", eventDataInXml.c_str() );

    //    return static_cast<int>( kbKeyStr[0] );
    //}

    //static std::vector<InputEvent> extractWriteTextData( const std::string &eventDataInXml )
    //{
    //    auto text = SimpleXmlParser::extractChildrenValue( "text", eventDataInXml.c_str() );
    //    std::vector<InputEvent> events;
    //    InputEvent event;


    //    for( auto &c : text )
    //    {
    //        event.type = KB_DOWN;
    //        event.kbKey = c;

    //        events.push_back( event );

    //        event.type = KB_UP;

    //        events.push_back( event );
    //    }
    //    return events;
    //}

    //static std::string extractData( const std::string &eventInXml, InputEvent &event )
    //{
    //    auto eventData = SimpleXmlParser::wholeChildrenValue( "data", 
    //                                                          eventInXml.c_str() );

    //    if( event.type == MOUSE_MOVE )
    //        event.mouseMoveTo = extractMouseMoveData( eventData );
    //    else 
    //        event.kbKey = extractKbKeyData( eventData );
    //}

    //static InputEvent extractSimpleEvent( const std::string &eventInXml )
    //{
    //    InputEvent event;

    //    event.type = extractType( eventInXml );

    //    if( event.isEventWithData() )
    //        extractData( eventInXml, event );

    //    return event;
    //}

    void extractWorkData( const char *taskData )
    {
        auto childrens = SimpleXmlParser::extractChildrens( "event", taskData );

        std::transform( childrens.begin(),
                        childrens.end(),
                        std::back_inserter(workData.eventsToExecute),
                        []( std::string &child )
                        {
                            auto type = extractType( child );
                            auto eventData = SimpleXmlParser::wholeChildrenValue( "data",
                                                                                  child.c_str() );

                            return eventsFactory->getEvent( type, eventData );
                        } );


        /*for( const auto &child : childrens )
        {
            auto type = extractType( child );


        }*/
    }

public:
    InputEventsWorker() :
        eventsFactory( std::make_shared<EventsFactory>() )
    {}
    ~InputEventsWorker() {}

    WorkerResultPtr doWork( const char *data )
    {
        try
        {
            auto sleepTime = std::chrono::milliseconds( defSleepTime );

            std::string taskData( data );

            extractWorkData( taskData.c_str() );

            //todo
            LOG( "InputEventsWorker::doWork" );

            for( auto &event : workData.eventsToExecute )
            {
                if( !event->execute() )
                    throw std::runtime_error( "Event execute failed" );

                std::this_thread::sleep_for( sleepTime );
            }

            return std::make_shared<SimpleWorkerResult>( RC_SUCCESS );//todo
        }
        catch( ... )
        {
            return std::make_shared<SimpleWorkerResult>( RC_FAIL );//todo
        }

        return std::make_shared<SimpleWorkerResult>( RC_FAIL );//todo
    }
};

