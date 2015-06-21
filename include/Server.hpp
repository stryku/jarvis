#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <array>
#include <set>

#include <TaskExecutor.hpp>
#include <RawMessage.hpp>
#include <MessageManager.hpp>

//#include <Session.hpp>
#include <ClientManager.hpp>

using boost::asio::ip::tcp;

class Server
{
private:
    ClientManager clientManager;
    tcp::socket socket;
    tcp::acceptor acceptor_;

    void do_accept( )
    {
        acceptor_.async_accept( socket,
                                [this]( boost::system::error_code ec )
        {
            if( !ec )
                clientManager.newClient( socket );

            do_accept( );
        } );
    }

public:
    Server( boost::asio::io_service& io_service,
            const tcp::endpoint& endpoint ) :
        acceptor_( io_service, endpoint ), 
        socket(io_service)
    {
        do_accept();
    }
    ~Server() {}
};

#endif