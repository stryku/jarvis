#ifndef XMLMESSAGE_HPP
#define XMLMESSAGE_HPP

#include <boost/asio.hpp>

#include <RawMessage.hpp>
#include <MessageTypeMap.hpp>
#include <XmlMessageCreator.hpp>

using boost::asio::ip::tcp;

class XmlMessage
{
protected:
    static MessageTypeMap messageTypeMap;

    MessageType type;
    XmlMessageCreator xmlMessageCreator;

    void createXmlDoc( void *dataPtr );
    virtual void createDataNode( void *dataPtr ) = 0;

public:
    XmlMessage( MessageType type );
    //XmlMessage( tcp::socket *socket );
    virtual ~XmlMessage( ) {}

    std::string toStdString();
    RawMessage toRawMessage( );


};

#endif // MESSAGE_HPP