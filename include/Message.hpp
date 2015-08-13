#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <ostream>

#include <MessageTypeEnum.h>

struct Message
{
    MessageType type;
    std::string id;
    bool needReply;
    std::string data;

    Message() {}
    ~Message() {}

    const char* getStrType() const
    {
        switch( type )
        {
            case XMSG_TASK: return "XMSG_TASK";
            case XMSG_OPTIONS: return "XMSG_OPTIONS";
            case XMSG_RECEIVED: return "XMSG_RECEIVED";
        }
    }

    friend std::ostream& operator<<( std::ostream &out, const Message &msg )
    {
        out << "type: " << msg.getStrType() 
            << "\nid: " << msg.id 
            << "\nneedReply: " << std::boolalpha << msg.needReply 
            << "\n" << msg.data;

        return out;
    }
};

#endif