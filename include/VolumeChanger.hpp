#ifndef _VOLUMECHANGER_HPP_
#define _VOLUMECHANGER_HPP_

#include <Worker.hpp>

#include <iostream>

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

    bool doWork( char *data )
    {
        WorkData *workData = reinterpret_cast<WorkData*>( data );

        std::cout << "Changing volume to: " << int( workData->newVolumePercents ) << "%\n";

        return true;
    }
};

#endif