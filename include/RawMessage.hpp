#ifndef RAWMESSAGE_HPP
#define RAWMESSAGE_HPP

#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class RawMessage
{
public:
    std::vector<char> data;
    size_t length;
    tcp::socket *socket;

    RawMessage( ) :
        length( 0 ),
        socket( nullptr )
    {
        data.resize( defaultVectorLength );
    }
    RawMessage( tcp::socket *socket, const std::string &stringData ) :
        socket( socket ),
        length( stringData.size() )
    {
        data.resize( length );
        std::copy( stringData.begin( ), stringData.end( ), data.begin( ) );
    }

    RawMessage( const RawMessage &message ) :
        length( message.length ),
        socket( message.socket )
    {
        const auto dataBegin = message.data.begin( ),
                   dataEnd = message.end();

        data.resize( length );
        std::copy( dataBegin, dataEnd, data.begin() );
    }

    ~RawMessage( ) {}

    std::string toStdString() const
    {
        return std::string( data.begin(), data.end() );
    }

private:
    static const size_t defaultVectorLength = 5 * 1024;

    std::vector<char>::const_iterator end( ) const
    {
        return data.begin( ) + length;
    }
};

#endif // RAWMESSAGE_HPP