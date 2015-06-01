#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_print.hpp>
#include <boost/asio.hpp>

#include <RawMessage.hpp>
#include <MessageTypeMap.hpp>

using namespace rapidxml;
using boost::asio::ip::tcp;

class XmlMessage
{
protected:
    static MessageTypeMap messageTypeMap;
    xml_document <> xmlDoc;
    tcp::socket *socket;
    MessageType type;

    void createBasicXml();
    void createXmlDoc( void *dataPtr );
    virtual void createDataNode( void *dataPtr ) = 0;


public:
    XmlMessage( MessageType type );
    XmlMessage( tcp::socket *socket );
    virtual ~XmlMessage( ) {}

    std::string toStdString() const;
    virtual RawMessage toRawMessage() = 0;


};

#endif // MESSAGE_HPP