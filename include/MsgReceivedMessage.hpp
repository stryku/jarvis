#ifndef _TASKRECEIVEDMESSAGE_HPP_
#define _TASKRECEIVEDMESSAGE_HPP_

#include <XmlDontNeedReplyMessage.hpp>

class MsgReceivedMessage : public XmlDontNeedReplyMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        auto &dataElem = xmlMessageCreator.dataElement;
        auto stringId = reinterpret_cast<std::string*>( dataPtr );

        dataElem.appendSimpleElement( "receivedmsgid", *stringId );
    }


public:
    MsgReceivedMessage( void *data ) :
        XmlDontNeedReplyMessage( XMSG_RECEIVED )
    {
        createXmlDoc( data );
    };
};


#endif