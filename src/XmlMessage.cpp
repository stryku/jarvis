#include <XmlMessage.hpp>

MessageTypeMap XmlMessage::messageTypeMap = MessageTypeMap();

XmlMessage::XmlMessage( MessageType type, tcp::socket *socketPtr ) :
    type( type ),
    socketPtr( socketPtr )
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

std::shared_ptr<RawMessage> XmlMessage::toRawMessage()
{
    return std::make_shared< RawMessage>( socketPtr, toStdString() );
}

