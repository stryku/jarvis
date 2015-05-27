#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <boost/asio.hpp>

#include <CustonAllocHandler.hpp>


using boost::asio::ip::tcp;


class session
    : public std::enable_shared_from_this<session>
{
public:
    session( tcp::socket socket )
        : socket_( std::move( socket ) )
    {}

    void start( )
    {
        do_read( );
    }

private:
    void do_read( )
    {
        auto self( shared_from_this( ) );
        socket_.async_read_some( boost::asio::buffer( data_ ),
                                 make_custom_alloc_handler( allocator_,
                                 [this, self]( boost::system::error_code ec, std::size_t length )
        {
            if( !ec )
            {
                do_write( length );
            }
        } ) );
    }

    void do_write( std::size_t length )
    {
        auto self( shared_from_this( ) );
        boost::asio::async_write( socket_, boost::asio::buffer( data_, length ),
                                  make_custom_alloc_handler( allocator_,
                                  [this, self]( boost::system::error_code ec, std::size_t /*length*/ )
        {
            if( !ec )
            {
                do_read( );
            }
        } ) );
    }

    // The socket used to communicate with the client.
    tcp::socket socket_;

    // Buffer used to store data received from the client.
    std::array<char, 1024> data_;

    // The allocator to use for handler-based custom memory allocation.
    handler_allocator allocator_;
};

#endif