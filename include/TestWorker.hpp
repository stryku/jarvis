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

    bool doWork(  const char *data )
    {
        std::cout << "Changing test value to: test\n";

        return true;
    }
};

#endif