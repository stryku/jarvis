#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

#include <MessageTypeEnum.h>

struct Message
{
    MessageType type;
    std::string id;
    bool needReply;
    std::string data;

    Message() {}
    ~Message() {}
};

#endif