#ifndef _WORKER_HPP_
#define _WORKER_HPP_

#include <WorkerResult.hpp>

#include <cstdint>
#include <memory>

class Worker
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    virtual void extractWorkData( const char *data ) = 0;

public:
    Worker() {}
    virtual ~Worker() {}

    virtual WorkerResultPtr doWork( const char *data ) = 0;
};

#endif