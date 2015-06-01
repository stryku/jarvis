#include <TaskTypeMap.hpp>

void TaskTypeMap::init( )
{
    add( "pc manage", TASK_PC_MANAGE );
    add( "jarvis manage", TASK_JARVIS_MANAGE );

    add( "test", TASK_TEST );
    add( "change volume", TASK_VOLUME_CHANGE );
}