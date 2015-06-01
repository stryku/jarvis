#ifndef _TASKSTRUCT_HPP_
#define _TASKSTRUCT_HPP_

#include <string>
#include <ostream>

#include <TaskTypeEnum.h>
#include <TaskTypeMap.hpp>
#include <WorkersFactory.hpp>

struct Task
{
    static TaskTypeMap taskTypeMap;

    TaskType type;
    std::string data;

    Task() {}
    Task( TaskType type, std::string data );
    ~Task() {}

    void execute()
    {
        auto worker = WorkersFactory::createWorker( type );

        worker->doWork( data.c_str() );
    }
};

std::ostream& operator<<( std::ostream &ostream, const Task &task );

#endif // _TASKSTRUCT_HPP_