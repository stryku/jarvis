#ifndef _XMLMESSAGECREATOR_HPP_
#define _XMLMESSAGECREATOR_HPP_

#include <vector>
#include <string>

#include <ComplexXmlElement.hpp>

class XmlMessageCreator
{
private:
    std::string typeString;
    std::string needReplyString;
    std::string id;

public:
    XmlMessageCreator() :
        dataElement( "data" )
    {}
    ~XmlMessageCreator() {}

    void addType( const std::string &type );
    void addNeedReply( const bool needReply );
    void addId( const std::string &id );
    void createBasicXml( XmlDocument &xmlDoc ) const;
    void createDataElement( XmlDocument &xmlDoc,
                            XmlNode *dataNode,
                            const SimpleXmlElement &dataElement ) const;

    void createDataNode( XmlDocument &xmlDoc ) const;
    std::string toStdString() const;

    ComplexXmlElement dataElement;
};

#endif