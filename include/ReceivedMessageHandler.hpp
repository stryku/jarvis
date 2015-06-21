#ifndef RECEIVEDMESSAGEHANDLER_HPP
#define RECEIVEDMESSAGEHANDLER_HPP

#include <iostream>

#include <RawMessage.hpp>

class ReceivedMessageHandler
{
public:
    ReceivedMessageHandler() {}
    ~ReceivedMessageHandler() {}

    static void handleMessage( const RawMessage rawMessage )
    {
        std::cout << "[ RECEIVED ]\n" << rawMessage.data << "\n\n";
    }
};

#endif