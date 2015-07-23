#ifndef SIMPLEXMLPARSER_HPP
#define SIMPLEXMLPARSER_HPP

#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_print.hpp>

#include <string>
#include <vector>
#include <memory>

class SimpleXmlParser
{
public:
    static std::string extractAsStdString( const std::string &xmlData )
    {
        xml_document <> doc;
        doc.parse<0>( const_cast<char*>( xmlData.c_str() ) );

        return std::string( doc.value() );
    }

    static std::string extractNode( const char *nodeName,
                                    const char *xmlData )
    {
        xml_document <> doc;
        doc.parse<0>( const_cast<char*>( xmlData ) );

        return std::string( doc.first_node( nodeName )->value( ) );
    }

    static std::string extractChildren( const char *nodeName,
                                        const char *xmlData )
    {
        xml_document <> doc;
        std::string stringData( xmlData );
        doc.parse<0>( const_cast<char*>( stringData.c_str() ) );
        auto root = doc.first_node();

        if( root != nullptr )
        {
            auto children = root->first_node( nodeName );

            if( children != nullptr )
                return std::string( children->value() );

            return std::string();
        }
    }
};

#endif