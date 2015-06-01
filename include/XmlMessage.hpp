#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <boost/asio.hpp>

#include <RawMessage.hpp>
#include <MessageTypeMap.hpp>
#include <XmlMessageCreator.hpp>

using boost::asio::ip::tcp;

class XmlMessage
{
protected:
    static MessageTypeMap messageTypeMap;

    tcp::socket *socketPtr;
    MessageType type;
    XmlMessageCreator xmlMessageCreator;

    void createXmlDoc( void *dataPtr );
    virtual void createDataNode( void *dataPtr ) = 0;

public:
    XmlMessage( MessageType type, tcp::socket *socketPtr );
    //XmlMessage( tcp::socket *socket );
    virtual ~XmlMessage( ) {}

    std::string toStdString();
    std::shared_ptr<RawMessage> toRawMessage( );


};

#endif // MESSAGE_HPP