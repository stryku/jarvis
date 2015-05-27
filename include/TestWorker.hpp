#ifndef _TESTWORKER_HPP_
#define _TESTWORKER_HPP_

#include <Worker.hpp>

#include <iostream>

class TestWorker : public Worker
{
private:
    struct WorkData
    {
        int32_t value;
    };

public:
    TestWorker( ) {}
    ~TestWorker( ) {}

    bool doWork( char *data )
    {
        WorkData *workData = reinterpret_cast<WorkData*>( data );

        std::cout << "Changing test value to: " << workData->value << "\n";

        return true;
    }
};

#endif