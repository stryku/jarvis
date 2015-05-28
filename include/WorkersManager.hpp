#ifndef _WORKERSMANAGER_HPP_
#define _WORKERSMANAGER_HPP_

#include <map>
#include <memory>

#include <WorkersMap.hpp>
#include <TaskTypeMap.hpp>

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

    bool doWork( TaskType taskType, const std::string &data )
    {
        return workersMap[taskType]->doWork( data.c_str() );
    }
};

#endif