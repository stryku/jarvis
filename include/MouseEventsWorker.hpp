#pragma once

#include <Worker.hpp>
#include <SimpleXmlParser.hpp>
#include <log.h>
#include <MouseEventsWorkerResult.hpp> // TODO

class MouseEventsWorker : public Worker //todo
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        //todo
    }workData;

    void extractWorkData( const char *taskData )
    {
        //todo

        /*auto data = SimpleXmlParser::extractChildren( "path", taskData );
        */
    }

public:
    MouseEventsWorker() {}
    ~MouseEventsWorker() {}

    WorkerResultPtr doWork( const char *data )
    {
        try
        {
            std::string taskData( data );

            extractWorkData( taskData.c_str() );

            //todo
            LOG( "" );

            //todo do work methods

            return std::make_shared<MouseEventsWorkerResult>( RC_SUCCESS );//todo
        }
        catch( ... )
        {
            return std::make_shared<MouseEventsWorkerResult>( RC_FAIL );//todo
        }

        return std::make_shared<MouseEventsWorkerResult>( RC_FAIL );//todo
    }
};