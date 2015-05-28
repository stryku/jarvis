#ifndef _TASKSTRUCT_HPP_
#define _TASKSTRUCT_HPP_

#include <string>

#include <TaskTypeEnum.h>

struct Task
{
    TaskType type;
    std::string data;

    Task() {}
    Task( TaskType type, std::string data ) :
        type( type ),
        data( data )
    {}
    ~Task() {}
};

#endif // _TASKSTRUCT_HPP_