#ifndef _TASKRECEIVEDMESSAGE_HPP_
#define _TASKRECEIVEDMESSAGE_HPP_

#include <XmlMessage.hpp>

class MsgReceivedMessage : public XmlMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        auto &dataElem = xmlMessageCreator.dataElement;
        auto stringId = reinterpret_cast<std::string*>( dataPtr );

        dataElem.appendSimpleElement( "receivedmsgid", *stringId );
    }

private:


public:
    MsgReceivedMessage( void *data ) :
        XmlMessage( XMSG_RECEIVED )
    {
        createXmlDoc( data );
    };
};


#endif