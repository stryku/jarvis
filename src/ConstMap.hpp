#ifndef _CONSTMAP_HPP_
#define _CONSTMAP_HPP_

#include "AbstractConstMap.hpp"

#include <memory>

#include <boost/bimap.hpp>

template <class Left, class Right>
class ConstMap : public AbstractConstMap
{
protected:
    typedef std::pair<Left, Right> ElementPair;
    typedef boost::bimap<Left, Right> Map;

    void add( const Left &left, const Right &right )
    {
        map.insert( typename Map::value_type( left, right ) );
    }

    Map map;

public:
    ConstMap() {}
    virtual ~ConstMap( ) {}

    const Right& operator[]( const Left &key )
    {
        return map.left.at( key );
    }
/*
    ValueType& get( const KeyType &key );
    KeyType& get( const ValueType &value );*/

   // getByValue

    const Left& operator[]( const Right &value )
    {
        return map.right.at( value );
    }
};

#endif // _CONSTMAP_HPP_
