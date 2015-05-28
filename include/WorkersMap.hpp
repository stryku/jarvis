#ifndef _WORKERSMAP_HPP_
#define _WORKERSMAP_HPP_

#include <ConstMap.hpp>
#include <WorkersFactory.hpp>

typedef WorkersFactory::WorkerType WorkerType;

class WorkersMap : public ConstMap<WorkerType, std::shared_ptr<Worker>>
{
private:

    void addWorker( WorkerType type )
    {
        map.insert( ElementPair( type,
                                 WorkersFactory::createWorker( type ) ) );
    }

    void init()
    {
        WorkerType begin = WorkerType::WT_VOLUME_CHANGER,
                   end = WorkerType::WT_END;

        for( size_t type = begin; type != end; ++type )
            addWorker( static_cast<WorkerType>( type ) );
    }

public:
    WorkersMap() {}
    ~WorkersMap() {}
};

#endif // _WORKERSMAP_HPP_