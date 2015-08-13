#ifndef _SIMPLEDATAELEMENT_HPP_
#define _SIMPLEDATAELEMENT_HPP_

#include <string>

struct SimpleXmlElement
{
    std::string name, value;

    SimpleXmlElement( const std::string &name,
                       const std::string &value ) :
                       name( name ),
                       value( value )
    {}
};

#endif // _SIMPLEDATAELEMENT_HPP_