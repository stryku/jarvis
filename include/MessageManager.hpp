#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include <queue>

#include <Message.hpp>
#include <MessageSender.hpp>

class MessageManager
{
private:
    bool sendingInProgress;

public:
    MessageManager() {}
    ~MessageManager() {}

    std::queue<RawMessage> receivedMessages;
    std::queue<RawMessage> messagesToSend;

    void receivedNewMessage( const RawMessage &message )
    {
        receivedMessages.push( message );
        // reply that we have received that message
        // execute task
    }

    void sendMessage()
    {
        if( !sendingInProgress )
        {
            sendingInProgress = true;

            while( !messagesToSend.empty() )
            {
                MessageSender::sendMessage( messagesToSend.front( ); );

                messagesToSend.pop();
            }

            sendingInProgress = false;
        }
    }
};

#endif // MESSAGEMANAGER_HPP