#ifndef _CONSTMAP_HPP_
#define _CONSTMAP_HPP_

#include <map>
#include <memory>

template <class KeyType, class ValueType>
class ConstMap
{
protected:
    typedef std::pair<KeyType, ValueType> ElementPair;
    typedef std::map<KeyType, ValueType> Map;

    Map map;

    virtual void init() = 0;

public:
    ConstMap();
    virtual ~ConstMap( ) {}

    const ValueType& operator[]( const KeyType &key ) const;

    const KeyType& operator[]( const ValueType &value ) const;
};

#endif // _CONSTMAP_HPP_