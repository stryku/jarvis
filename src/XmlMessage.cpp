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

std::string XmlMessage::toStdString() const
{
    return xmlMessageCreator.toStdString();
}

XmlMessage::ZmqMessagePtr XmlMessage::toZmqMessage( ) const
{
    auto strMessage = toStdString();
    return std::make_shared<zmq::message_t>( strMessage.begin(), strMessage.end() );
}

