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
    TaskReceivedMessage( void *data ) : XmlMessage( XMSG_TASK_RECEIVED )
    {
        createXmlDoc( data );
    };
    TaskReceivedMessage( tcp::socket *socket, void *data ) :
        XmlMessage( socket )
    {};


    RawMessage toRawMessage( )
    {
        RawMessage rawMessage;

        return rawMessage;
    };
};


#endif