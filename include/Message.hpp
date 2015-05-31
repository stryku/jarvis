#ifndef RECEIVEDMESSAGE_HPP
#define RECEIVEDMESSAGE_HPP

#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct Message
{
    static const size_t defaultVectorLength = 5 * 1024;

    std::vector<char> data;
    size_t length;
    tcp::socket *socket;

    Message( ) : 
        length( 0 ),
        socket( nullptr )
    {
        data.resize( defaultVectorLength );
    }
    Message( const Message &message ) : 
        length( message.length ),
        socket( message.socket )
    {
        const auto dataBegin = message.data.begin( ),
                   dataEnd = message.end();

        data.resize( length );
        std::copy( dataBegin, dataEnd, data.begin() );
    }
    ~Message( ) {}

    std::vector<char>::const_iterator end() const
    {
        return data.begin() + length;
    }

};

#endif // RECEIVEDMESSAGE_HPP