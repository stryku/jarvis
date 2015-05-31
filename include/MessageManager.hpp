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

    std::queue<Message> receivedMessages;
    std::queue<Message> messagesToSend;

    void receivedNewMessage( const Message &message )
    {
        receivedMessages.push( message );
    }

    void sendMessage()
    {
        if( !sendingInProgress )
        {
            sendingInProgress = true;

            while( !messagesToSend.empty() )
            {
                Message &message = messagesToSend.front();

                MessageSender::sendMessage( *message.socket, message.toStdString() );

                messagesToSend.pop();
            }

            sendingInProgress = false;
        }
    }
};

#endif // MESSAGEMANAGER_HPP