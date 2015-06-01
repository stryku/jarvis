#include <MessageTypeMap.hpp>

void MessageTypeMap::init( )
{
    add( "task received", XMSG_TASK_RECEIVED );
    add( "test", XMSG_TEST );
}