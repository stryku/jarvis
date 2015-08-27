#pragma once

#include "Worker.hpp"
#include "SimpleXmlParser.hpp"
#include "log.h"
#include "SimpleWorkerResult.hpp"
#include "InputEventTypeMap.hpp"
#include "InputEventsFactory.hpp"

#include <string>
#include <mutex>
#include <thread>
#include <memory>

class InputEventsWorker : public Worker
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;
    typedef std::shared_ptr<AbstractEvent> AbstractEventPtr;
    typedef std::unique_ptr<InputEventsFactory> EventsFactoryPtr;
    
    static const size_t defSleepTime = 2000;
    

    static InputEventTypeMap eventTypeMap;
    static EventsFactoryPtr eventsFactory;

    struct WorkData
    {
        std::vector<AbstractEventPtr> eventsToExecute;
    }workData;

    static InputEventType extractType( const std::string &eventInXml )
    {
        auto stringType = SimpleXmlParser::extractChildren( "type", 
                                                            eventInXml.c_str() );

        return eventTypeMap[stringType];
    }

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
    }

public:
    InputEventsWorker()
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

