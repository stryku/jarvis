#ifndef _XMLMESSAGECREATOR_HPP_
#define _XMLMESSAGECREATOR_HPP_

#include <vector>
#include <string>

#include <ComplexDataElement.hpp>


class XmlMessageCreator
{
private:
    std::string typeString;

public:
    XmlMessageCreator() :
        dataElement( "data" )
    {}
    ~XmlMessageCreator() {}

    void addType( const std::string &type );
    void createBasicXml( XmlDocument &xmlDoc );
    void createDataElement( XmlDocument &xmlDoc,
                            XmlNode *dataNode,
                            const SimpleDataElement &dataElement );

    void createDataNode( XmlDocument &xmlDoc );
    std::string toStdString();

    ComplexDataElement dataElement;
};

#endif