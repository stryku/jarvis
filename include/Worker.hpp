#ifndef _WORKER_HPP_
#define _WORKER_HPP_

#include <cstdint>

class Worker
{
public:
    Worker() {}
    virtual ~Worker() {}

    virtual bool doWork( const char *data ) = 0;
};

#endif