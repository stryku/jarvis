#ifndef _VOLUMECHANGER_HPP_
#define _VOLUMECHANGER_HPP_

#include <Worker.hpp>
#include <VolumeChangerResult.hpp>
#include <SimpleXmlParser.hpp>
#include <log.h>

#include <iostream>

#include <Windows.h>

class VolumeChanger : public Worker
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        int8_t newVolumePercents;
    }workData;

    void extractWorkData( const char *taskData )
    {
        auto data = SimpleXmlParser::extractChildren( "newvalue", taskData );

        workData.newVolumePercents = static_cast<int8_t>( std::stoi( data ) );
    }

public:
    VolumeChanger( ) {}
    ~VolumeChanger( ) {}

    WorkerResultPtr doWork( const char *data )
    {
        //waveOutSetVolume( NULL, 100 );
        std::string taskData( data );
        extractWorkData( taskData.c_str() );
        LOG( "Changing volume to " << static_cast<int>( workData.newVolumePercents ) );

        return std::make_shared<VolumeChangerResult>( true );
    }
};

#endif