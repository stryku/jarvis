#ifndef RECEIVEDMESSAGEHANDLER_HPP
#define RECEIVEDMESSAGEHANDLER_HPP

#include <iostream>

#include <RawMessage.hpp>
#include <Client.hpp>

class ReceivedMessageHandler
{
    typedef std::shared_ptr<Client> ClientPtr;
public:
    ReceivedMessageHandler() {}
    ~ReceivedMessageHandler() {}

    static void handleMessage( const RawMessage rawMessage,
                               const ClientPtr &clientPtr )
    {
        std::cout << "[ RECEIVED ]\n" << rawMessage.toStdString() << "\n\n";
    }
};

#endif