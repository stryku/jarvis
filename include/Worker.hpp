#ifndef _WORKER_HPP_
#define _WORKER_HPP_

#include <cstdint>
#include <memory>
#include <WorkerResult.hpp>

typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

class Worker
{
public:
    Worker() {}
    virtual ~Worker() {}

    virtual WorkerResultPtr doWork( const char *data ) = 0;
};

#endif