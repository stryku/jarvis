#ifndef _TASKTYPEMAP_HPP_
#define _TASKTYPEMAP_HPP_

#include <string>

#include <ConstMap.hpp>
#include <TaskTypeEnum.h>

class TaskTypeMap : public ConstMap<const std::string&, TaskType>
{
private:

    void addTaskType( const std::string &taskString, TaskType taskType )
    {
        map.insert( ElementPair( taskString, taskType ) );
    }

    void init()
    {
        addTaskType( "PC Manage Task", TASK_PC_MANAGE );
        addTaskType( "Jarvis Manage Task", TASK_JARVIS_MANAGE );

        addTaskType( "test", TASK_TEST );
        addTaskType( "change volume", TASK_VOLUME_CHANGE );
    }

public:
    TaskTypeMap() {};
    ~TaskTypeMap() {}
};

#endif