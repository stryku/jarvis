#include <XmlMessage.hpp>

MessageTypeMap XmlMessage::messageTypeMap = MessageTypeMap();

XmlMessage::XmlMessage( MessageType type ) :
    type( type )
{}
//
//XmlMessage::XmlMessage( tcp::socket *socket ) :
//    socket( socket )
//{}

void XmlMessage::createXmlDoc( void *dataPtr )
{
    xmlMessageCreator.addType( messageTypeMap[type] );
    createDataNode( dataPtr );
}

std::string XmlMessage::toStdString( )
{
    return xmlMessageCreator.toStdString();
}

RawMessage XmlMessage::toRawMessage( )
{
    return RawMessage( toStdString() );
}

