#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include <queue>
#include <boost/lockfree/queue.hpp>

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
                RawMessage tmp;
                messagesToSend.pop( tmp );
                MessageSender::sendMessage( tmp );
            }

            sendingInProgress = false;
        }
    }

    void newMessageToExecute( const RawMessage &rawMessage )
    {

    }

    boost::lockfree::queue<RawMessage> receivedMessages;
    boost::lockfree::queue<RawMessage> messagesToSend;

public:
    MessageManager() : 
        sendingInProgress( false ) 
    {}
    ~MessageManager() {}

    void receivedNewMessage( const RawMessage &message )
    {
        receivedMessages.push( message );
        auto replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASK_RECEIVED, message.socketPtr );
        // reply that we have received that message - need xml message factory
        newMessageToSend( replyMessage->toRawMessage( ) );
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