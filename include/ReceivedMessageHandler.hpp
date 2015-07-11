#ifndef RECEIVEDMESSAGEHANDLER_HPP
#define RECEIVEDMESSAGEHANDLER_HPP

#include <iostream>

#include <RawMessage.hpp>
#include <Client.hpp>
#include <ClientManager.hpp>
#include <XmlMessageParser.hpp>
#include <IdentifyMessage.hpp>

class ReceivedMessageHandler
{
private:
    typedef std::shared_ptr<Client> ClientPtr;
    typedef std::shared_ptr<Message> MessagePtr;

    static ClientManager &clientManager;

    static void handleIdentify( const MessagePtr &message,
                                const ClientPtr &clientPtr )
    {
        IdentifyMessage identifyMessage( message );

        clientManager.newClientId( &clientPtr->socket, 
                                   identifyMessage.clientId );
    }

public:
    ReceivedMessageHandler() {}
    ~ReceivedMessageHandler() {}

    static void handleMessage( const RawMessage rawMessage,
                               const ClientPtr &clientPtr )
    {
        std::cout << "[ RECEIVED ]\n" << rawMessage.toStdString() << "\n\n";
        auto message = XmlMessageParser::extract( rawMessage.toStdString().c_str() );

        switch( message->type )
        {
            case XMSG_IDENTIFY: handleIdentify( message, clientPtr ); break;
        }
    }

    static void setClientManager( ClientManager &newClientManager )
    {
        clientManager = newClientManager;
    }
};

#endif