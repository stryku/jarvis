#ifndef _MAPMIRROR_HPP_
#define _MAPMIRROR_HPP_

#include <map>

template <class KeyType, class ValueType>
class MapMirror
{
private:
    typename std::map<ValueType, KeyType> OutMapType;
    typename std::map<KeyType, ValueType> InMapType;

    typename std::pair<ValueType, KeyType> OutPair;
    typename std::pair<KeyType, ValueType> InPair;

    static OutPair mirrorPair( const InPair &inPair )
    {
        return OutPair( inPair.second, inPair.first );
    }
public:


    static OutMapType mirrorMap( const InMapType &inMap )
    {
        OutMapType outMap;

        for( const auto &it : inMap )
            outMap.insert( mirrorPair( *it ) );

        return outMap;
    }
}
#endif // _MAPMIRROR_HPP_

