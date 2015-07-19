#ifndef MESSAGETOSEND_HPP
#define MESSAGETOSEND_HPP

#include <PersonalMessage.hpp>
#include <XmlMessage.hpp>

struct MessageToSend
{
    std::string id;
    PersonalMessage personalMsg;

    MessageToSend( const std::string &id,
                   const XmlMessage *xmlMessage,
                   const zmq::message_t &identity ) :
        id( id ),
        personalMsg( identity, *( xmlMessage->toZmqMessage( ).get( ) ) )
    {}

};

#endif