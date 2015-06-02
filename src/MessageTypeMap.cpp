#include <MessageTypeMap.hpp>

void MessageTypeMap::init( )
{
    add( "task received", XMSG_TASK_RECEIVED );
    add( "test", XMSG_TEST );
    add( "tasks started", XMSG_TASKS_STARTED );
    add( "tasks finished", XMSG_TASKS_FINISHED );
}