#ifndef _COMPLEXDATAELEMENT_HPP_
#define _COMPLEXDATAELEMENT_HPP_

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <vector>
#include <cstdint>

#include <SimpleDataElement.hpp>

using namespace rapidxml;

typedef xml_document<> XmlDocument;
typedef xml_node<> XmlNode;

class ComplexDataElement
{
private:
    std::vector<SimpleDataElement> simpleElements;
    std::vector<ComplexDataElement> complexElements;
    std::string name;

    void toXmlNode( XmlNode *node )
    {

    }

public:
    ComplexDataElement( const std::string &name ) :
        name( name )
    {}

    void appendSimpleElement( const std::string &name,
                              const std::string &value )
    {
        simpleElements.push_back( SimpleDataElement( name, value ) );
    }

    void appendSimpleElement( const std::string &name,
                              const char value )
    {
        char buf[2];
        buf[0] = value;
        buf[1] = '\0';

        simpleElements.push_back( SimpleDataElement( name, buf ) );
    }

    void appendSimpleElement( const std::string &name,
                              const int32_t value )
    {
        simpleElements.push_back( SimpleDataElement( name,
                                                     std::to_string( value ) ) );
    }

    void appendSimpleElement( const std::string &name,
                              const size_t value )
    {
        simpleElements.push_back( SimpleDataElement( name,
                                                     std::to_string( value ) ) );
    }

    void appendSimpleElement( const std::string &name,
                              const bool value )
    {
        simpleElements.push_back( SimpleDataElement( name,
                                                     ( value ? "true" : "false" ) ) );
    }

    ComplexDataElement& newComplexDataElement( const std::string &name )
    {
        complexElements.push_back( ComplexDataElement( name ) );

        return complexElements.back( );
    }

    void createSimpleElement( XmlDocument &xmlDoc,
                            XmlNode *dataNode,
                            const SimpleDataElement &dataElement ) const
    {
        auto dataElementNode = xmlDoc.allocate_node( node_element,
                                                     dataElement.name.c_str( ),
                                                     dataElement.value.c_str( ) );

        dataNode->append_node( dataElementNode );
    }

    XmlNode* toXmlNode( XmlDocument &xmlDoc ) const
    {
        auto dataNode = xmlDoc.allocate_node( node_element, name.c_str() );

        for( const auto &simpleElement : simpleElements )
            createSimpleElement( xmlDoc, dataNode, simpleElement );

        for( const auto &complexElement : complexElements )
        {
            auto node = complexElement.toXmlNode( xmlDoc );
            dataNode->append_node( node );
        }

        return dataNode;
    }
};

#endif // _COMPLEXDATAELEMENT_HPP_