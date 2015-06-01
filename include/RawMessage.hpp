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
    tcp::socket *socketPtr;

    RawMessage( ) :
        length( 0 ),
        socketPtr( nullptr )
    {
        data.resize( defaultVectorLength );
    }
    RawMessage( tcp::socket *socket, const std::string &stringData ) :
        socketPtr( socket ),
        length( stringData.size() )
    {
        data.resize( length );
        std::copy( stringData.begin( ), stringData.end( ), data.begin( ) );
    }

    RawMessage( const RawMessage &message ) :
        length( message.length ),
        socketPtr( message.socketPtr )
    {
        const auto dataBegin = message.data.begin( ),
                   dataEnd = message.end();

        data.resize( length );
        std::copy( dataBegin, dataEnd, data.begin() );
    }

    ~RawMessage( ) {}

    std::string toStdString() const
    {
        std::string a( data.begin(), end() );

        return std::string( data.begin(), end() );
    }

private:
    static const size_t defaultVectorLength = 5 * 1024;

    std::vector<char>::const_iterator end( ) const
    {
        return data.begin( ) + length;
    }
};

#endif // RAWMESSAGE_HPP