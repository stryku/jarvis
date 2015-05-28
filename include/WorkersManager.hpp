#ifndef _WORKERSMANAGER_HPP_
#define _WORKERSMANAGER_HPP_

#include <map>
#include <memory>

#include <WorkersMap.hpp>
#include <TaskTypeEnum.h>

class WorkersManager
{
private:
    WorkersMap workersMap;
    TaskTypeMap taskTypeMap;

public:
    WorkersManager() 
    {
    }
    ~WorkersManager() {}

    bool doWork( TaskType taskType, char *data )
    {
        return workersMap[taskType]->doWork( data );
    }

    bool doWork( TaskType taskType, const std::string &data )
    {
        return doWork( taskType, data.c_str() );
    }
};

#endif