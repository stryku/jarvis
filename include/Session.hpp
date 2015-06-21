#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <boost/asio.hpp>
//#include <MessageManager.hpp>
//#include <XMLTaskParser.hpp>
//#include <TaskExecutor.hpp>

#include <Client.hpp>
#include <ReceivedMessageHandler.hpp>

using boost::asio::ip::tcp;

class Session 
{
private:
    typedef std::shared_ptr<Client> ClientPtr;

    static const size_t messageLengthBuffSize = 20;

    char messageLengthBuff[messageLengthBuffSize];
    RawMessage receivedMessage;
    ClientPtr client;
    
    void readMessageLength( )
    {
        boost::asio::async_read( client->socket,
                                 boost::asio::buffer( messageLengthBuff, messageLengthBuffSize ),
                                 [this]( boost::system::error_code ec, std::size_t )
        {
            if( !ec )
            {
                receivedMessage.length = atoi( messageLengthBuff );
                readMessage( );
            }
        } );
    }

    void readMessage( )
    {
        boost::system::error_code errorCode;
        bool extractedSize = false;
        size_t readedSize = 0;
        int32_t messageLength;

        boost::asio::async_read( client->socket,
                                 boost::asio::buffer( receivedMessage.data, receivedMessage.length ),
                                 [this]( boost::system::error_code ec, std::size_t /*length*/ )
        {
            if( !ec )
            {
                receivedMessage.data[receivedMessage.length] = '\0';
                ReceivedMessageHandler::handleMessage( receivedMessage, client );
                readMessageLength( );
            }
        } );
    }

public:
    Session( ClientPtr client ) :
        client( client )
    {}
    ~Session( ) {}

    void start( )
    {
        readMessageLength();
    }
};

#endif