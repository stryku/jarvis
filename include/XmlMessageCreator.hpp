#ifndef _XMLMESSAGECREATOR_HPP_
#define _XMLMESSAGECREATOR_HPP_

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <vector>
#include <string>

using namespace rapidxml;

class XmlMessageCreator
{
private:
    struct DataElement
    {
        std::string name, value;

        DataElement( const std::string &name, 
                     const std::string &value ) :
            name( name ),
            value( value )
        {}
    };

    typedef xml_document<> XmlDocument;
    typedef xml_node<> XmlNode;

    std::vector<DataElement> dataElements;
    std::string typeString;

public:
    XmlMessageCreator() {}
    ~XmlMessageCreator() {}

    void addTypeString( const std::string &type )
    {
        typeString = type;
    }

    void addDataElement( const std::string &name,
                         const std::string &value )
    {
        dataElements.push_back( DataElement( name, value ) );
    }

    void createBasicXml( XmlDocument &xmlDoc )
    {
        auto msg = xmlDoc.allocate_node( node_element, "msg" );
        auto typeNode = xmlDoc.allocate_node( node_element, "type", typeString.c_str( ) );

        msg->append_node( typeNode );

        xmlDoc.append_node( msg );
    }

    void createDataElement( XmlDocument &xmlDoc,
                            XmlNode *dataNode, 
                            const DataElement &dataElement )
    {
        auto dataElementNode = xmlDoc.allocate_node( node_element, 
                                                     dataElement.name.c_str(),
                                                     dataElement.value.c_str() );

        dataNode->append_node( dataElementNode );
    }

    void createDataNode( XmlDocument &xmlDoc )
    {
        auto dataNode = xmlDoc.allocate_node( node_element, "data" );

        for( const auto dataElement : dataElements )
            createDataElement( xmlDoc, dataNode, dataElement );

        xmlDoc.first_node( )->append_node( dataNode );
    }

    std::string toStdString()
    {
        std::string ret;
        XmlDocument xmlDoc;

        createBasicXml( xmlDoc );
        createDataNode( xmlDoc );

        print( std::back_inserter( ret ), xmlDoc, 0 );

        return ret;
    }
};

#endif