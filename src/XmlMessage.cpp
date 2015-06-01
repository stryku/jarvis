#include <XmlMessage.hpp>

MessageTypeMap XmlMessage::messageTypeMap = MessageTypeMap();


void XmlMessage::createXmlDoc( void *dataPtr )
{
    xmlMessageCreator.addType( messageTypeMap[type] );
    createDataNode( dataPtr );
}

XmlMessage::XmlMessage( MessageType type ) : type( type )
{

}
XmlMessage::XmlMessage( tcp::socket *socket ) :
socket( socket )
{}

std::string XmlMessage::toStdString( )
{
    return xmlMessageCreator.toStdString();
}


