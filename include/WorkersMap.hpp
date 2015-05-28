#ifndef _WORKERSMAP_HPP_
#define _WORKERSMAP_HPP_

#include <ConstMap.hpp>
#include <WorkersFactory.hpp>

class WorkersMap : public ConstMap<TaskType, std::shared_ptr<Worker>>
{
private:

    void addWorker( TaskType type )
    {
        map.insert( ElementPair( type,
                                 WorkersFactory::createWorker( type ) ) );
    }

    void init()
    {
        TaskType begin, end;

        begin = static_cast<TaskType>( TASK_BEGIN + 1 );
        end = TASK_END;

        for( size_t type = begin; type != end; ++type )
            addWorker( static_cast<TaskType>( type ) );
    }

public:
    WorkersMap() {}
    ~WorkersMap() {}
};

#endif // _WORKERSMAP_HPP_