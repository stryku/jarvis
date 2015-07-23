#ifndef _COMPLEXDATAELEMENT_HPP_
#define _COMPLEXDATAELEMENT_HPP_

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <vector>
#include <cstdint>

#include <SimpleXmlElement.hpp>

using namespace rapidxml;

typedef xml_document<> XmlDocument;
typedef xml_node<> XmlNode;

class ComplexXmlElement
{
private:
    std::vector<SimpleXmlElement> simpleElements;
    std::vector<ComplexXmlElement> complexElements;
    std::string name, value;

    void toXmlNode( XmlNode *node )
    {

    }

public:
    ComplexXmlElement( const std::string &name, 
                        const std::string &value = std::string() ) :
        name( name ),
        value( value )
    {}

    void appendComplexElement( const ComplexXmlElement &elem )
    {
        complexElements.push_back( elem );
    }

    void appendSimpleElement( const std::string &name,
                              const std::string &value )
    {
        simpleElements.push_back( SimpleXmlElement( name, value ) );
    }

    void appendSimpleElement( const std::string &name,
                              const char *value )
    {
        simpleElements.push_back( SimpleXmlElement( name, value ) );
    }

    void appendSimpleElement( const std::string &name,
                              const char value )
    {
        char buf[2];
        buf[0] = value;
        buf[1] = '\0';

        simpleElements.push_back( SimpleXmlElement( name, buf ) );
    }

    void appendSimpleElement( const std::string &name,
                              const int32_t value )
    {
        simpleElements.push_back( SimpleXmlElement( name,
                                                     std::to_string( value ) ) );
    }

    void appendSimpleElement( const std::string &name,
                              const uint64_t value )
    {
        simpleElements.push_back( SimpleXmlElement( name,
                                                     std::to_string( value ) ) );
    }

    void appendSimpleElement( const std::string &name,
                              const bool value )
    {
        simpleElements.push_back( SimpleXmlElement( name,
                                                     ( value ? "true" : "false" ) ) );
    }

    ComplexXmlElement& newComplexXmlElement( const std::string &name )
    {
        complexElements.push_back( ComplexXmlElement( name ) );

        return complexElements.back();
    }

    void createSimpleElement( XmlDocument &xmlDoc,
                            XmlNode *dataNode,
                            const SimpleXmlElement &dataElement ) const
    {
        auto dataElementNode = xmlDoc.allocate_node( node_element,
                                                     dataElement.name.c_str( ),
                                                     dataElement.value.c_str( ) );

        dataNode->append_node( dataElementNode );
    }

    XmlNode* toXmlNode( XmlDocument &xmlDoc ) const
    {
        auto dataNode = xmlDoc.allocate_node( node_element, name.c_str(), value.c_str() );

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