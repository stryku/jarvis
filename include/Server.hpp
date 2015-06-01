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
    std::array<char, 2048> data;
    RawMessage receivedMessage;


public:
    Server( boost::asio::io_service& io_service ) :
        socket(io_service)
    {}
    ~Server() {}

    int32_t readMessageLength()
    {
        const size_t bufSize = 5;

        char buf[bufSize];
        int32_t receivedLength;
        boost::system::error_code errorCode;
        

        socket.read_some( boost::asio::buffer( buf, bufSize ),
                          errorCode );

        if( errorCode )
            throw boost::system::system_error( errorCode );

        return *( reinterpret_cast<int32_t*>( buf ) );
    }

    size_t readPartOfMessage( boost::system::error_code &ec )
    {
        return socket.read_some( boost::asio::buffer( receivedMessage.data ),
                                 ec );
    }

    void readMessage()
    {
        boost::system::error_code errorCode;
        bool extractedSize = false;
        size_t readedSize = 0;
        int32_t messageLength;

        messageLength = readMessageLength();

        do
        {
            readedSize += readPartOfMessage( errorCode );

        } while( !errorCode && readedSize < messageLength );

        if( errorCode )
            throw boost::system::system_error( errorCode );


        receivedMessage.socketPtr = &socket;
        receivedMessage.length = messageLength;
        receivedMessage.data[receivedMessage.length] = '\0';
        //data[readedSize] = '\0';
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

        return 0;
    }

    MessageManager messageManager;
    tcp::socket socket;
};

#endif