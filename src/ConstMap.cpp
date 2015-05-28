//#include <ConstMap.hpp>
//
//template <class KeyType, class ValueType>
//ConstMap<KeyType, ValueType>::ConstMap( )
//{
//    init();
//}
//
//template <class KeyType, class ValueType>
//const ValueType& ConstMap<KeyType, ValueType>::operator[]( const KeyType &key ) const
//{
//    return map[key];
//}
//
////template <class KeyType, class ValueType>
////ValueType& ConstMap<KeyType, ValueType>::get( const KeyType &key )
////{
////    return map[key];
////}
//
////template <class KeyType, class ValueType>
////KeyType& ConstMap<KeyType, ValueType>::get( const ValueType &value )
////{
////    return map.find( value )->first;
////}
//template <class KeyType, class ValueType>
//const KeyType& ConstMap<KeyType, ValueType>::operator[]( const ValueType &value ) const
//{
//    return map.find( value )->first;
//}