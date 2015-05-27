#ifndef _CONSTMAP_HPP_
#define _CONSTMAP_HPP_

#include <map>
#include <memory>

template <class KeyType, class ValueType>
class ConstMap
{
private:
    typedef std::pair<KeyType, std::shared_ptr<ValueType>> ElementPair;

    std::map<KeyType, ValueType> map;

    void createElement( KeyType keyType, ValueType value )
    {
        map.insert( ElementPair( KeyType,
                    std::make_shared<ValueType>( value ) ) );
    }

    virtual void init() = 0;

public:
    ConstMap()
    {
        init();
    }
    virtual ~ConstMap( ) {}

    const ValueType& operator[]( const KeyType &key ) const
    {
        return map[key];
    }
};

#endif // _CONSTMAP_HPP_