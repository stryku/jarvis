#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <array>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct Client
{
    tcp::socket socket;
    std::string id;

    Client( tcp::socket socket ) :
        socket( std::move( socket ) )
    {}
    ~Client() {}
};

#endif