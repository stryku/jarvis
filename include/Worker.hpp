#ifndef _WORKER_HPP_
#define _WORKER_HPP_

class Worker
{
public:
    Worker() {}
    virtual ~Worker() {}

    virtual doWork( char *data ) = 0;
};

#endif