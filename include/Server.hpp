#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <Session.hpp>

class Server
{
public:
    Server( boost::asio::io_service& io_service, short port )
        : acceptor_( io_service, tcp::endpoint( tcp::v4( ), port ) ),
        socket_( io_service )
    {
        do_accept( );
    }

private:
    void do_accept( )
    {
        acceptor_.async_accept( socket_,
                                [this]( boost::system::error_code ec )
        {
            if( !ec )
            {
                std::make_shared<session>( std::move( socket_ ) )->start( );
            }

            do_accept( );
        } );
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

#endif