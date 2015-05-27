#ifndef _HANDLERALLOCATOR_HPP_
#define _HANDLERALLOCATOR_HPP_

#include <memory>

class handler_allocator
{
public:
    handler_allocator( )
        : in_use_( false )
    {}

    handler_allocator( const handler_allocator& ) = delete;
    handler_allocator& operator=( const handler_allocator& ) = delete;

    void* allocate( std::size_t size )
    {
        if( !in_use_ && size < sizeof( storage_ ) )
        {
            in_use_ = true;
            return &storage_;
        }
        else
        {
            return ::operator new( size );
        }
    }

    void deallocate( void* pointer )
    {
        if( pointer == &storage_ )
        {
            in_use_ = false;
        }
        else
        {
            ::operator delete( pointer );
        }
    }

private:
    // Storage space used for handler-based custom memory allocation.
    std::aligned_storage<1024>::type storage_;

    // Whether the handler-based custom allocation storage has been used.
    bool in_use_;
};

#endif