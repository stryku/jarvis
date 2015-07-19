#ifndef XMLNEEDREPLYMESSAGE_HPP
#define XMLNEEDREPLYMESSAGE_HPP

#include <XmlMessage.hpp>

class XmlNeedReplyMessage : public XmlMessage
{
public:
    XmlNeedReplyMessage( MessageType type ) :
        XmlMessage( type, true )
    {}
    virtual ~XmlNeedReplyMessage() {}
};

#endif