#ifndef RAWMESSAGE_HPP
#define RAWMESSAGE_HPP

#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class RawMessage
{
public:
    std::vector<char> data;
    int32_t length;

    RawMessage( ) :
        length( 0 )
    {
        data.resize( defaultVectorLength );
    }
    RawMessage( const std::string &stringData ) :
        length( stringData.size() )
    {
        data.resize( length );
        std::copy( stringData.begin( ), stringData.end( ), data.begin( ) );
    }

    RawMessage( const RawMessage &message ) :
        length( message.length )
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