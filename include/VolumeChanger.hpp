#ifndef _VOLUMECHANGER_HPP_
#define _VOLUMECHANGER_HPP_

#include <Worker.hpp>
#include <VolumeChangerResult.hpp>

#include <iostream>

#include <Windows.h>

class VolumeChanger : public Worker
{
private:
    struct WorkData
    {
        int8_t newVolumePercents;
    };

public:
    VolumeChanger( ) {}
    ~VolumeChanger( ) {}

    WorkerResultPtr doWork( const char *data )
    {
        std::cout << "Changing volume to: 50%\n";
        //waveOutSetVolume( NULL, 100 );

        return std::make_shared<VolumeChangerResult>( true );
    }
};

#endif