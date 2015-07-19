#ifndef XMLMESSAGE_HPP
#define XMLMESSAGE_HPP

#include <MessageTypeMap.hpp>
#include <XmlMessageCreator.hpp>

#include <zmq.hpp>

class XmlMessage
{
protected:
    typedef std::shared_ptr<zmq::message_t> ZmqMessagePtr;

    static MessageTypeMap messageTypeMap;

    MessageType type;
    XmlMessageCreator xmlMessageCreator;

    void createXmlDoc( void *dataPtr );
    virtual void createDataNode( void *dataPtr ) = 0;

public:
    XmlMessage( MessageType type );
    //XmlMessage( tcp::socket *socket );
    virtual ~XmlMessage( ) {}

    std::string toStdString() const;
    ZmqMessagePtr toZmqMessage() const;


};

#endif // MESSAGE_HPP