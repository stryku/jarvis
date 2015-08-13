#ifndef THREADSAFEQUEUE_HPP
#define THREADSAFEQUEUE_HPP

#include <queue>
#include <deque>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>

template<class T>
class ThreadSafeQueue : public std::queue<T>
{
private:
    typedef typename
        std::queue<T>::container_type::const_iterator const_iterator;

public:
    T pop()
    {
        std::unique_lock<std::mutex> mlock( mutex_ );

        while( c.empty( ) )
            cond_.wait( mlock );

        auto item = c.front( );
        c.pop_front();
        return item;
    }

    void pop( T& item )
    {
        std::unique_lock<std::mutex> mlock( mutex_ );
        while( c.empty( ) )
        {
            cond_.wait( mlock );
        }
        item = c.pop_front( );
        c.pop( );
    }

    void push( const T& item )
    {
        std::unique_lock<std::mutex> mlock( mutex_ );
        c.push_back( item );
        mlock.unlock( );
        cond_.notify_one( );
    }

    void push( T&& item )
    {
        std::unique_lock<std::mutex> mlock( mutex_ );
        c.push_back( std::move( item ) );
        mlock.unlock( );
        cond_.notify_one( );
    }

    void erase( const T &item )
    {
        std::unique_lock<std::mutex> mlock( mutex_ );

        auto it = find( item );

        if( it != c.end( ) )
            c.erase( it );

        mlock.unlock();
    }

    bool isInside( const T &item )
    {
        std::unique_lock<std::mutex> mlock( mutex_ );

        auto findRet = std::find( c.begin(), c.end(), item ) != c.end();

        mlock.unlock( );

        return findRet;
    }

    const_iterator find( const T &item )
    {
        std::unique_lock<std::mutex> mlock( mutex_ );

        auto findRet = std::find( c.begin(), c.end(), item );

        mlock.unlock();

        return findRet;
    }

private:
    //std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif