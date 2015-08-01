#pragma once

#include <utility>

template <typename T>
class Point
{
private:
    std::pair<T, T> pair;

public:
    T &x, &y;

    Point() :
        x( pair.first ),
        y( pair.second )
    {}
    Point( const T &x, const T &y ) :
        pair( { x, y } ),
        x( pair.first ),
        y( pair.second )
    {}
    ~Point() {}
};