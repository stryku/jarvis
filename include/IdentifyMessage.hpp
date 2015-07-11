#ifndef IDENTIFYMESSAGE_HPP
#define IDENTIFYMESSAGE_HPP

#include <string>

#include <Message.hpp>
#include <SimpleXmlParser.hpp>

struct IdentifyMessage
{
    typedef std::shared_ptr<Message> MessagePtr;

    std::string clientId;

    IdentifyMessage( const MessagePtr &message )
    {
        clientId = SimpleXmlParser::extractAsStdString( message->data );
    }
    ~IdentifyMessage() {}
};

#endif