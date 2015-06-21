#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

#include <MessageTypeEnum.h>
#include <RawMessage.hpp>

class Message
{
protected:
    MessageType type;
    std::string id;
    bool needReply;

public: 
    Message() {}
    virtual ~Message() {}

    virtual void fromRawMessage( const RawMessage &rawMessage ) = 0;
};

#endif