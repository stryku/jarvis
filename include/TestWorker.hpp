#ifndef _TESTWORKER_HPP_
#define _TESTWORKER_HPP_

#include <Worker.hpp>
#include <TestWorkerResult.hpp>

#include <iostream>

class TestWorker : public Worker
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        int32_t value;
    };

public:
    TestWorker( ) {}
    ~TestWorker( ) {}

    WorkerResultPtr doWork( const char *data )
    {
        std::cout << "Changing test value to: test\n";

        return std::make_shared<TestWorkerResult>( true );
    }
};

#endif