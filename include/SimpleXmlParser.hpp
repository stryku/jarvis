#ifndef SIMPLEXMLPARSER_HPP
#define SIMPLEXMLPARSER_HPP

#include <string>
#include <vector>
#include <memory>

#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_print.hpp>

class SimpleXmlParser
{
public:
    static std::string extractAsStdString( const std::string &xmlData )
    {
        xml_document <> doc;
        doc.parse<0>( const_cast<char*>( xmlData.c_str() ) );

        return std::string( doc.value() );
    }
};

#endif