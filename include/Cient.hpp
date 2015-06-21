#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <array>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct Client
{
    static const size_t defaultBufferSize = 1024;

    tcp::socket socket;
    std::string id;
    std::array<char, defaultBufferSize> buffer;

    Client( tcp::socket socket ) :
        socket( std::move( socket ) )
    {}
};

#endif