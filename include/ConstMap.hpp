#ifndef _CONSTMAP_HPP_
#define _CONSTMAP_HPP_

#include <map>
#include <memory>

#include <boost/bimap.hpp>

template <class KeyType, class ValueType>
class ConstMap
{
protected:
    typedef std::pair<KeyType, ValueType> ElementPair;
    //typedef std::map<KeyType, ValueType> Map;

    typedef boost::bimap<KeyType, ValueType> Map;

    Map map;


    virtual void init() = 0;

public:
    ConstMap()
    {
        init();
    }
    virtual ~ConstMap( ) {}

    const ValueType& operator[]( const KeyType &key )
    {
        return map.left.at( key );
    }
/*
    ValueType& get( const KeyType &key );
    KeyType& get( const ValueType &value );*/

   // getByValue

    KeyType& operator[]( const ValueType &value )
    {
        return map.right.at( value );
    }
};

#endif // _CONSTMAP_HPP_