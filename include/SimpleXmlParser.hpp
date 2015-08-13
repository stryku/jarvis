#ifndef SIMPLEXMLPARSER_HPP
#define SIMPLEXMLPARSER_HPP

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

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

    static std::string extractChildrenValue( const char *nodeName,
                                             xml_node<char> *root )
    {
        if( root == nullptr )
            return std::string();
        
        auto children = root->first_node( nodeName );

        if( children != nullptr )
            return std::string( children->value() );

        return std::string();
    }

    static std::string wholeNodeValue( xml_node<char> *node )
    {
        if( node != nullptr )
        {
            std::string ret;
            print( std::back_inserter( ret ), *node, 0 );
            return ret;
        }

        return std::string();
    }

    static std::string wholeChildrenValue( const char *nodeName,
                                           const char *xmlData )
    {
        xml_document <> doc;
        std::string stringData( xmlData );
        doc.parse<0>( const_cast<char*>( stringData.c_str() ) );
        auto root = doc.first_node();

        if( root == nullptr )
            return std::string();

        auto children = root->first_node( nodeName );

        if( children == nullptr )
            return std::string();

        return wholeNodeValue( children );
    }

    static std::string extractChildrenValue( const char *nodeName,
                                             const char *xmlData )
    {
        xml_document <> doc;
        std::string stringData( xmlData );
        doc.parse<0>( const_cast<char*>( stringData.c_str() ) );
        auto root = doc.first_node();

        return extractChildrenValue( nodeName, root );
    }

    static std::string extractChildren( const char *childrenName,
                                        const char *xmlData )
    {
        return extractChildrenValue( childrenName,
                                     xmlData );
    }

    static std::vector<std::string> extractChildrens( std::string childrensName,
                                                      const char *xmlData )
    {
        xml_document <> doc;
        std::string stringData( xmlData );
        doc.parse<0>( const_cast<char*>( stringData.c_str() ) );
        auto root = doc.first_node();
        std::vector<std::string> childrens;
        xml_node<char> *currentChildren = root->first_node();

        while( currentChildren != nullptr )
        {
            if( currentChildren->name() == childrensName )
            {
                auto childrenValue = wholeNodeValue( currentChildren );
                childrens.push_back( childrenValue );
            }

            root->remove_node( currentChildren );

            currentChildren = root->first_node();
        }

        return childrens;
    }
};

#endif
