#ifndef _WORKERSMANAGER_HPP_
#define _WORKERSMANAGER_HPP_

#include <map>
#include <memory>

#include <WorkersMap.hpp>

class WorkersManager
{
private:
    WorkersMap workersMap;

public:
    WorkersManager() 
    {
    }
    ~WorkersManager() {}

    bool doWork( WorkerType workerType, char *data )
    {
        return workersMap[workerType]->doWork( data );
    }
};

#endif