#ifndef MESSAGESENDER_HPP
#define MESSAGESENDER_HPP

#include <string>
#include <boost/asio.hpp>

#include <RawMessage.hpp>
#include <Session.hpp>

using boost::asio::ip::tcp;

class MessageSender
{
private:

    /*Session &session;

    void sendMessages()
    {
        if( !sendingInProgress )
        {
            sendingInProgress = true;

            while( !messagesToSend.empty( ) )
            {
                MessagePtr tmp;
                MessageSender::sendMessage( messagesToSend.front( ) );

                messagesToSendMutex.lock( );
                messagesToSend.pop( );
                messagesToSendMutex.unlock( );

            }

            sendingInProgress = false;
        }
    }

public:
    MessageSender( Session &session ) :
        session( session )
    {}

    void sendMessage( const std::shared_ptr<RawMessage> message )
    {
        boost::asio::async_write( *( message->socketPtr ),
                                  boost::asio::buffer( message->toStdString( ) ),
                                  []( boost::system::error_code ec, size_t writtenBytesCount ) 
                                  {   
                                      if( !ec )
                                          throw boost::system::system_error( ec );
                                  } );
    }

    void newMessageToSend( std::shared_ptr<RawMessage> &rawMessage )
    {
        messagesToSendMutex.lock( );
        messagesToSend.push( rawMessage );
        messagesToSendMutex.unlock( );
        sendMessages( );
    }*/
};

#endif // MESSAGESENDER_HPP