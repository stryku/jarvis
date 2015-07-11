#include <MessageTypeMap.hpp>

void MessageTypeMap::init( )
{
    add( "identify", XMSG_IDENTIFY );
    add( "task", XMSG_TASK );
    add( "options", XMSG_OPTIONS);
}