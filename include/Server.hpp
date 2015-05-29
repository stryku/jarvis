#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <TaskExecutor.hpp>
#include <array>

using boost::asio::ip::tcp;

class Server
{
private:
    TaskExecutor taskExecutor;
    std::array<char, 2048> data;


public:
    Server( boost::asio::io_service& io_service ) :
        socket(io_service)
    {}
    ~Server() {}

    void readMessage( )
    {
        boost::system::error_code errorCode;
        bool extractedSize = false;
        size_t messageSize, readedSize = 0;

        do
        {
            readedSize += socket.read_some( boost::asio::buffer( data ),
                                            errorCode );

            if( !extractedSize )
            {
                uint32_t *ptr = reinterpret_cast<uint32_t*>( data.data( ) );
                messageSize = *ptr;
                extractedSize = true;
            }

        } while( !errorCode && readedSize < messageSize );

        if( errorCode )
            throw boost::system::system_error( errorCode );

        data[readedSize] = '\0';
    }

    void responseToMessage( )
    {
        char data[10] = "PRZYJALEM";
        socket.write_some( boost::asio::buffer( data, 10 ) );
    }

    /*void do_read( )
    {
        boost::system::error_code errorCode;

        while( 1 )
        {
            if( ( errorCode = readMessage() ) == boost::system::errc::success )
                responseToMessage( );
            else
        }
    }*/

    int run()
    {
        tcp::acceptor acceptor( socket.get_io_service( ), tcp::endpoint( tcp::v4( ), 21020 ) );

        acceptor.accept( socket );

        for( ;; )
        {
            readMessage();
            //std::cout << data.data() + 4;
            taskExecutor.execute( data.data()+4 );
            responseToMessage();
        }
    }

    tcp::socket socket;
};

#endif