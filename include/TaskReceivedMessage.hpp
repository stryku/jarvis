#ifndef _TASKRECEIVEDMESSAGE_HPP_
#define _TASKRECEIVEDMESSAGE_HPP_


#include <XmlMessage.hpp>

class TaskReceivedMessage : public XmlMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        xmlMessageCreator.addDataElement( "succes", true );
    }

private:


public:
    TaskReceivedMessage( tcp::socket *socketPtr, void *data ) :
        XmlMessage( XMSG_TASK_RECEIVED, socketPtr )
    {
        createXmlDoc( data );
    };
};


#endif