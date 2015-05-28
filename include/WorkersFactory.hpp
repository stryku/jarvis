#ifndef _WORKERSFACTORY_HPP_
#define _WORKERSFACTORY_HPP_

#include <memory>

#include <Workers.h>
#include <TaskTypeEnum.h>

class WorkersFactory
{
public:
    WorkersFactory() {}
    ~WorkersFactory() {}

    static std::shared_ptr<Worker> createWorker( TaskType type )
    {
        switch( type )
        {
            case TASK_TEST:             return std::make_shared<TestWorker>(); 
            case TASK_VOLUME_CHANGE:    return std::make_shared<VolumeChanger>(); 
            default:                    return std::make_shared<TestWorker>(); 
        }
    }
};

#endif // _WORKERSFACTORY_HPP_