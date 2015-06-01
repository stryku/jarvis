#ifndef _MESSAGETYPEMAP_HPP_
#define _MESSAGETYPEMAP_HPP_

#include <string>

#include <ConstMap.hpp>
#include <MessageTypeEnum.h>

class MessageTypeMap : public ConstMap<const std::string, MessageType>
{
private:
    void init();

public:
    MessageTypeMap() { init(); }
    ~MessageTypeMap() {}
};

#endif // _MESSAGETYPEMAP_HPP_