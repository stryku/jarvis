#ifndef _CUSTOMALLOCHANDLER_HPP_
#define _CUSTOMALLOCHANDLER_HPP_

#include <HandlerAllocator.hpp>

template <typename Handler>
class custom_alloc_handler
{
public:
    custom_alloc_handler( handler_allocator& a, Handler h )
        : allocator_( a ),
        handler_( h )
    {}

    template <typename ...Args>
    void operator()( Args&&... args )
    {
        handler_( std::forward<Args>( args )... );
    }

    friend void* asio_handler_allocate( std::size_t size,
                                        custom_alloc_handler<Handler>* this_handler )
    {
        return this_handler->allocator_.allocate( size );
    }

    friend void asio_handler_deallocate( void* pointer, std::size_t /*size*/,
                                         custom_alloc_handler<Handler>* this_handler )
    {
        this_handler->allocator_.deallocate( pointer );
    }

private:
    handler_allocator& allocator_;
    Handler handler_;
};

template <typename Handler>
inline custom_alloc_handler<Handler> make_custom_alloc_handler(
    handler_allocator& a, Handler h )
{
    return custom_alloc_handler<Handler>( a, h );
}

#endif