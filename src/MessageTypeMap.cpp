#include <MessageTypeMap.hpp>

void MessageTypeMap::init( )
{
    add( "XMSG_TASK", XMSG_TASK );
    add( "XMSG_OPTIONS", XMSG_OPTIONS );
    add( "XMSG_RECEIVED", XMSG_RECEIVED );
    add( "XMSG_TASK_FINISHED", XMSG_TASK_FINISHED ); 
    add( "XMSG_RESULT", XMSG_RESULT );
}