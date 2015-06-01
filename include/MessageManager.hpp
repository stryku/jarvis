#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include <queue>

#include <MessageSender.hpp>
#include <XmlMessageFactory.hpp>

class MessageManager
{
private:
    bool sendingInProgress;

    void sendMessages( )
    {
        if( !sendingInProgress )
        {
            sendingInProgress = true;

            while( !messagesToSend.empty( ) )
            {
                MessageSender::sendMessage( messagesToSend.front( ); );

                messagesToSend.pop( );
            }

            sendingInProgress = false;
        }
    }

public:
    MessageManager() : 
        sendingInProgress( false ) 
    {}
    ~MessageManager() {}

    std::queue<RawMessage> receivedMessages;
    std::queue<RawMessage> messagesToSend;

    void receivedNewMessage( const RawMessage &message )
    {
        receivedMessages.push( message );
        // reply that we have received that message - need xml message factory
        newMessageToSend( XmlMessageFactory::generateXmlMessage( XMSG_TASK_RECEIVED )->toRawMessage() );
        //      
        // execute task - need task executor
    }

    void newMessageToSend( const RawMessage &rawMessage )
    {
        messagesToSend.push( rawMessage );
        sendMessages();
    }

    
};

#endif // MESSAGEMANAGER_HPP