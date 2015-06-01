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

    void createBasicXml()
    {
        auto msg = xmlDoc.allocate_node( node_element, "msg" );
        auto typeNode = xmlDoc.allocate_node( node_element, "type", messageTypeMap[type].c_str() );

        msg->append_node( typeNode );

        xmlDoc.append_node( msg );
    }

    void createXmlDoc( void *dataPtr )
    {
        createBasicXml( );
        createDataNode( dataPtr );
    }

    virtual void createDataNode( void *dataPtr ) = 0;


public:
    XmlMessage( ) {}
    XmlMessage( tcp::socket *socket ) :
        socket( socket )
    {}
    virtual ~XmlMessage( ) {}

    std::string toStdString() const
    {
        std::string ret;

        print( std::back_inserter( ret ), doc, 0 );

        return ret;
    }

    virtual RawMessage toRawMessage() = 0;


    MessageType type;
};

#endif // MESSAGE_HPP