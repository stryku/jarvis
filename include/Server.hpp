#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <array>

#include <TaskExecutor.hpp>
#include <RawMessage.hpp>
#include <MessageManager.hpp>

using boost::asio::ip::tcp;

class Server
{
private:
    TaskExecutor taskExecutor;
    std::array<char, 2048> data;
    RawMessage receivedMessage;


public:
    Server( boost::asio::io_service& io_service ) :
        socket(io_service)
    {}
    ~Server() {}

    size_t readMessageLength()
    {
        int32_t receivedLength;
        boost::system::error_code errorCode;

        socket.read_some( boost::asio::buffer( &receivedLength, sizeof( int32_t ) ),
                          errorCode );

        if( !errorCode )
            throw boost::system::system_error( errorCode );

        return receivedLength;
    }

    void readMessage()
    {
        boost::system::error_code errorCode;
        bool extractedSize = false;
        size_t messageLength, readedSize = 0;

        messageLength = readMessageLength();

        do
        {
            readedSize += socket.read_some( boost::asio::buffer( receivedMessage.data ),
                                            errorCode );


        } while( !errorCode && readedSize < messageLength );

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

    void readMessages()
    {
        for( ;; )
        {
            readMessage();
            messageManager.receivedNewMessage( receivedMessage );
        }
    }

    int run()
    {
        tcp::acceptor acceptor( socket.get_io_service( ), tcp::endpoint( tcp::v4( ), 21020 ) );

        acceptor.accept( socket );

        readMessages();
    }

    MessageManager messageManager;
    tcp::socket socket;
};

#endif