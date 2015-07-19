#ifndef XMLDONTNEEDREPLYMESSAGE_HPP
#define XMLDONTNEEDREPLYMESSAGE_HPP

#include <XmlMessage.hpp>

class XmlDontNeedReplyMessage : public XmlMessage
{
public:
    XmlDontNeedReplyMessage( MessageType type ) :
        XmlMessage( type, false )
    {}
    virtual ~XmlDontNeedReplyMessage( ) {}
};

#endif