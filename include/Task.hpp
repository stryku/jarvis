#ifndef _TASKSTRUCT_HPP_
#define _TASKSTRUCT_HPP_

#include <string>
#include <ostream>

#include <TaskTypeEnum.h>
#include <TaskTypeMap.hpp>

struct Task
{
    static const TaskTypeMap taskTypeMap;

    TaskType type;
    std::string data;

    Task() {}
    Task( TaskType type, std::string data ) :
        type( type ),
        data( data )
    {}
    ~Task() {}

    std::ostream& operator<<( std::ostream &ostream )
    {
        ostream << "Task type: " << taskTypeMap[type] << "\n"
                << "Data:\n" << data;
    }

};

#endif // _TASKSTRUCT_HPP_