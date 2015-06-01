#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_print.hpp>

enum MessageType
{
    MSG_TASK_RECEIVED
};

class XmlMessage
{
private:
    xml_document <> doc;

public:
    XmlMessage( ) {}
    ~XmlMessage( ) {}

    std::string toStdString() const
    {
        std::string ret;

        print( std::back_inserter( ret ), doc, 0 );

        return ret;
    }


    MessageType type;
};

#endif // MESSAGE_HPP