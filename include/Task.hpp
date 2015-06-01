#ifndef _TASKSTRUCT_HPP_
#define _TASKSTRUCT_HPP_

#include <string>
#include <ostream>
#include <mutex>

#include <TaskTypeEnum.h>
#include <TaskTypeMap.hpp>
#include <WorkersFactory.hpp>

class Task
{
private:
    static TaskTypeMap taskTypeMap;
    static uint32_t tasksCount;
    static std::mutex taskCountMutex;

    size_t idNumber;

    void assignIdNumber()
    {
        taskCountMutex.lock();
        idNumber = tasksCount++;
        taskCountMutex.unlock();
    }

public:
    TaskType type;
    std::string data;

    Task() { assignIdNumber(); }
    Task( TaskType type, std::string data );
    ~Task() {}

    void execute()
    {
        auto worker = WorkersFactory::createWorker( type );

        worker->doWork( data.c_str() );
    }

    size_t getIdNumber() const
    {
        return idNumber;
    }

    std::string stringType() const
    {
        return taskTypeMap[type];
    }
};

#endif // _TASKSTRUCT_HPP_