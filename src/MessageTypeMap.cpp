#include <MessageTypeMap.hpp>

void MessageTypeMap::init( )
{
    add( "identif", XMSG_IDENTIFY );
    add( "task", XMSG_TASK );
    add( "options", XMSG_OPTIONS);
}