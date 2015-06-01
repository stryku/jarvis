#include <MessageTypeMap.hpp>

void MessageTypeMap::init( )
{
    add( "received task", XMSG_RECEIVED_TASK );
    add( "test", XMSG_TEST );
}