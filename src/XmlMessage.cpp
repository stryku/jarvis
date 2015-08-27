#include <XmlMessage.hpp>

MessageTypeMap XmlMessage::messageTypeMap = MessageTypeMap();

XmlMessage::XmlMessage( MessageType type, bool needReply ) :
    id( MessageIdGenerator::get() ), 
    type( type ),
    needReply( needReply )
{}
//
//XmlMessage::XmlMessage( tcp::socket *socket ) :
//    socket( socket )
//{}

void XmlMessage::createXmlDoc( void *dataPtr )
{
    xmlMessageCreator.addType( messageTypeMap[type] );
    xmlMessageCreator.addNeedReply( needReply );
    xmlMessageCreator.addId( id );
    createDataNode( dataPtr );
}

std::string XmlMessage::toStdString() const
{
    return xmlMessageCreator.toStdString();
}

XmlMessage::ZmqMessagePtr XmlMessage::toZmqMessage( ) const
{
    auto strMessage = toStdString() + '\0';
    return std::make_shared<zmq::message_t>( const_cast<char*>(strMessage.c_str() ),
                                             strMessage.size(),
                                             nullptr );
}

