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

    bool doWork( const char *data )
    {
        std::cout << "Changing volume to: 50%\n";

        return true;
    }
};

#endif