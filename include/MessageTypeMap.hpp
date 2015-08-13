#ifndef _MESSAGETYPEMAP_HPP_
#define _MESSAGETYPEMAP_HPP_

#include <ConstMap.hpp>
#include <MessageTypeEnum.h>

#include <string>

class MessageTypeMap : public ConstMap<const std::string, MessageType>
{
private:
    void init();

public:
    MessageTypeMap() { init(); }
    ~MessageTypeMap() {}
};

#endif // _MESSAGETYPEMAP_HPP_