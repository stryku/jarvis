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
    }

    void sendMessage()
    {
        if( !sendingInProgress )
        {
            sendingInProgress = true;

            while( !messagesToSend.empty() )
            {
                RawMessage &rawMessage = messagesToSend.front( );

                MessageSender::sendMessage( *( rawMessage.socket ),
                                            rawMessage.toStdString( ) );

                messagesToSend.pop();
            }

            sendingInProgress = false;
        }
    }
};

#endif // MESSAGEMANAGER_HPP