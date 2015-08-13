#ifndef XMLMESSAGEPARSER_HPP
#define XMLMESSAGEPARSER_HPP

#include <string>
#include <vector>
#include <memory>

#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_print.hpp>

#include <Message.hpp>
#include <MessageTypeMap.hpp>

using namespace rapidxml;

class XmlMessageParser
{
private:
    typedef std::shared_ptr<Message> MessagePtr;

    static MessageTypeMap messageTypeMap;
   
    static bool parseNeedReply( const char *needReplyString )
    {
        return std::string( needReplyString ) == "true";
    }

    static std::string extractId( const xml_node<> *msgNode )
    {
        const char *idString;

        idString = msgNode->first_node( "id" )->value( );

        return std::string( idString );
    }
    static MessageType extractType( const xml_node<> *msgNode )
    {
        const char *typeString;

        typeString = msgNode->first_node( "type" )->value( );

        return messageTypeMap[typeString];
    }
    static bool extractNeedReply( const xml_node<> *msgNode )
    {
        const char *needReplyString;

        needReplyString = msgNode->first_node( "needreply" )->value( );

        return parseNeedReply( needReplyString );
    }
    static std::string extractData( const xml_node<> *msgNode )
    {
        auto dataNode = msgNode->first_node( "data" );
        std::string ret;

        print( std::back_inserter( ret ), *dataNode, 0 );

        return ret;
    }

public:
    XmlMessageParser( ) {}
    ~XmlMessageParser( ) {}

    static MessagePtr extract( const char *xmlData )
    {
        auto message = std::make_shared<Message>();
        xml_document <> doc;
        doc.parse<0>( const_cast<char*>( xmlData ) );
        auto *msgNode = doc.first_node( );

        message->id = extractId( msgNode );
        message->type = extractType( msgNode );
        message->data = extractData( msgNode );
        message->needReply = extractNeedReply( msgNode );

        return message;
    }
};

#endif