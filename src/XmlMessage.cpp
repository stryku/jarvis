#include <XmlMessage.hpp>

MessageTypeMap XmlMessage::messageTypeMap = MessageTypeMap();

void XmlMessage::createBasicXml( )
{
    auto msg = xmlDoc.allocate_node( node_element, "msg" );
    auto typeNode = xmlDoc.allocate_node( node_element, "type", messageTypeMap[type].c_str( ) );

    msg->append_node( typeNode );

    xmlDoc.append_node( msg );
}

void XmlMessage::createXmlDoc( void *dataPtr )
{
    createBasicXml( );
    createDataNode( dataPtr );
}

XmlMessage::XmlMessage( MessageType type ) : type( type )
{

}
XmlMessage::XmlMessage( tcp::socket *socket ) :
socket( socket )
{}

std::string XmlMessage::toStdString( ) const
{
    std::string ret;

    print( std::back_inserter( ret ), xmlDoc, 0 );

    return ret;
}


