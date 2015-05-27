#ifndef _WORKERSFACTORY_HPP_
#define _WORKERSFACTORY_HPP_

#include <memory>

#include <Workers.h>

class WorkersFactory
{
public:
    enum WorkerType
    {
        WT_TEST,
        WT_VOLUME_CHANGER
    };

    WorkersFactory() {}
    ~WorkersFactory() {}

    static std::shared_ptr<Worker> createWorker( WorkerType type )
    {
        switch( type )
        {
            case WT_TEST:           return std::make_shared<TestWorker>();
            case WT_VOLUME_CHANGER: return std::make_shared<VolumeChanger>();
        }
    }
};

#endif // _WORKERSFACTORY_HPP_