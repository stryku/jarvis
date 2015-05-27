#ifndef _STATICMAP_HPP_
#define _STATICMAP_HPP_

#include <map>
#include <memory>

template <class KeyType, class ValueType>
class StaticMap
{
private:
    static std::map<KeyType, ValueType> map;
    typedef  std::pair<KeyType, std::unique_ptr<ValueType>> ElementPair;

    static void createElement( KeyType keyType, ValueType value )
    {
        map.insert( ElementPair( KeyType,
                    std::make_unique<ValueType>( value ) ) );
    }

    virtual void init() = 0;

public:
    StaticMap()
    {
        init();
    }
    virtual ~StaticMap() {}

    ValueType& operator[]( const KeyType &
};

#endif