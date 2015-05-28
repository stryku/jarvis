#ifndef _TASKTYPEMAP_HPP_
#define _TASKTYPEMAP_HPP_

#include <string>

#include <ConstMap.hpp>
#include <TaskTypeEnum.h>

class TaskTypeMap : public ConstMap<const std::string, TaskType>
{
private:

    void addTaskType( const std::string &taskString, TaskType taskType );
    void init();

public:
    TaskTypeMap() 
    {
        init();
    }
    ~TaskTypeMap() {}
};

#endif