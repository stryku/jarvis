#ifndef XMLMESSAGE_HPP
#define XMLMESSAGE_HPP

#include <MessageTypeMap.hpp>
#include <XmlMessageCreator.hpp>
#include <MessageIdGenerator.hpp>

#include <zmq.hpp>

class XmlMessage
{
protected:
    typedef std::shared_ptr<zmq::message_t> ZmqMessagePtr;

    static MessageTypeMap messageTypeMap;

    std::string id;
    MessageType type;
    bool needReply;
    XmlMessageCreator xmlMessageCreator;

    void createXmlDoc( void *dataPtr );
    virtual void createDataNode( void *dataPtr ) = 0;

public:
    XmlMessage( MessageType type, bool needReply );
    //XmlMessage( tcp::socket *socket );
    virtual ~XmlMessage( ) {}

    std::string toStdString() const;
    ZmqMessagePtr toZmqMessage() const;

    std::string getId() const
    {
        return id;
    }

};

#endif // MESSAGE_HPP