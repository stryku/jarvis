#ifndef _TASKRECEIVEDMESSAGE_HPP_
#define _TASKRECEIVEDMESSAGE_HPP_


#include <XmlMessage.hpp>

class TaskReceivedMessage : public XmlMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        auto &dataElem = xmlMessageCreator.dataElement;
        dataElem.appendSimpleElement( "succes", true );
    }

private:


public:
    TaskReceivedMessage( void *data ) :
        XmlMessage( XMSG_TASK_RECEIVED )
    {
        createXmlDoc( data );
    };
};


#endif