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
    boost::system::error_code readMessage()
    {
        boost::system::error_code errorCode;
        bool extractedSize = false;
        size_t messageSize, readedSize = 0;


        do
        {
            readedSize += socket_.read_some( boost::asio::buffer( data_ ),
                                             errorCode );

            if( !extractedSize )
            {
                uint32_t *ptr = reinterpret_cast<uint32_t*>( data_.data() );
                messageSize = *ptr;
                extractedSize = true;
            }

        } while( errorCode || readedSize == messageSize );

        return errorCode;
    }

    void do_read( )
    {
        auto self( shared_from_this( ) );
        boost::system::error_code errorCode;

        while( 1 )
        {
            if( ( errorCode = readMessage() ) != boost::system::errc::success )
                std::cerr << "Reading message failed. Error code: " << errorCode << "\n";
            else
            {
                std::cout << "Reading message succesfull. Message:\n" << data_.data() + 4;
            }
        }
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