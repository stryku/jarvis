#ifndef _WORKERSMANAGER_HPP_
#define _WORKERSMANAGER_HPP_

#include <map>
#include <memory>

#include <Workers.h>

class WorkersManager
{
private:
    enum WorkerType
    {
        WT_VOLUME_CHANGER = 0,
        WT_TEST
    };

    typedef  std::map<WorkerType, std::unique_ptr<Worker>> WorkersMap;
    typedef  std::pair<WorkerType, std::unique_ptr<Worker>> WorkerPair;

    WorkersMap workersMap;
    
    template <class WorkerClass>
    void createWorker( WorkerType workerType )
    {
        workersMap.insert( WorkerPair( workerType,
                                       std::make_unique<WorkerClass>() ) );
    }

    void initWorkersMap()
    {
        createWorker<VolumeChanger> ( WT_VOLUME_CHANGER );
        createWorker<TestWorker>    ( WT_TEST );
    }

public:
    WorkersManager() 
    {
        initWorkersMap();
    }
    ~WorkersManager() {}

    bool doWork( WorkerType workerType, char *data )
    {
        return workersMap[workerType]->doWork( data );
    }
};

#endif