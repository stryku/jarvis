#include <WorkersMap.hpp>

void WorkersMap::addWorker( TaskType type )
{
    map.insert( Map::value_type( type,
                                 WorkersFactory::createWorker( type ) ) );
}

void WorkersMap::init( )
{
    TaskType begin, end;

    begin = static_cast<TaskType>( TASK_BEGIN + 1 );
    end = TASK_END;

    for( size_t type = begin; type != end; ++type )
        addWorker( static_cast<TaskType>( type ) );
}