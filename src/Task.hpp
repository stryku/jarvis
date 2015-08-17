#ifndef _TASKSTRUCT_HPP_
#define _TASKSTRUCT_HPP_

#include "TaskTypeEnum.h"
#include "TaskTypeMap.hpp"
#include "WorkersFactory.hpp"

#include <string>
#include <ostream>
#include <mutex>

class Task
{
private:
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    static TaskTypeMap taskTypeMap;
    static std::size_t tasksCount;

    std::size_t idNumber;

    void assignIdNumber()
    {
        idNumber = tasksCount++;
    }

    void determineIfFast()
    {
        auto fastTasksTypes = { TASK_VOLUME_CHANGE,
                                TASK_GET_FOLDER_CONTENT,
                                TASK_RENAME_DIR_ENTRY,
                                TASK_INPUT_EVENTS };

        fastTask = std::any_of( fastTasksTypes.begin(),
                                fastTasksTypes.end(),
                                [this]( TaskType i ) { return i == type; } );
    }

public:
    TaskType type;
    std::string data;
    std::string id;
    WorkerResultPtr result;
    bool fastTask;

    Task() 
    { 
        assignIdNumber(); 
        determineIfFast();
    }
    Task( TaskType type, std::string data, std::string id );
    ~Task() {}

    void execute()
    {
        auto worker = WorkersFactory::createWorker( type );

        result = worker->doWork( data.c_str() );

    }

    std::size_t getIdNumber() const
    {
        return idNumber;
    }

    std::string stringType() const
    {
        return taskTypeMap[type];
    }
};

#endif // _TASKSTRUCT_HPP_
