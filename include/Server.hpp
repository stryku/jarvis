#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <array>
#include <set>

#include <TaskExecutor.hpp>
#include <RawMessage.hpp>
#include <MessageManager.hpp>

#include <Session.hpp>

using boost::asio::ip::tcp;

class Server
{
private:
    std::array<char, 2048> data;
    std::set<std::shared_ptr<Session>> sessions;

public:
    Server( boost::asio::io_service& io_service,
            const tcp::endpoint& endpoint ) :
        acceptor_( io_service, endpoint ), 
        socket(io_service)
    {
        do_accept();
    }
    ~Server() {}

    /*int32_t readMessageLength()
    {
        const size_t bufSize = 20;

        char buf[bufSize];
        int32_t receivedLength;
        boost::system::error_code errorCode;
        

        socket.read_some( boost::asio::buffer( buf, bufSize ),
                          errorCode );

        if( errorCode )
            throw boost::system::system_error( errorCode );

        return atoi( buf );
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
    }

    void readMessages()
    {
        for( ;; )
        {
            readMessage();
            messageManager.receivedNewMessage( receivedMessage );
        }
    }*/

    void do_accept( )
    {
        acceptor_.async_accept( socket,
                                [this]( boost::system::error_code ec )
        {
            if( !ec )
            {

                auto session = std::make_shared<Session>( std::move( socket ) );
                sessions.insert( session );
                session->start();
            }

            do_accept( );
        } );
    }

    //MessageManager messageManager;
    tcp::socket socket;
    tcp::acceptor acceptor_;
};

#endif