#ifndef _TESTWORKER_HPP_
#define _TESTWORKER_HPP_

#include <Worker.hpp>

#include <iostream>

class VolumeChanger : public Worker
{
private:
    struct WorkData
    {
        int32_t value;
    };

public:
    VolumeChanger( ) {}
    ~VolumeChanger( ) {}

    bool doWork( char *data )
    {
        WorkData *workData = reinterpret_cast<WorkData*>( data );

        std::cout << "Changing test value to: " << workData->value << "\n";

        return true;
    }
};

#endif