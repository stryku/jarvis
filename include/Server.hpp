#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <PersonalMessage.hpp>
#include <RequestHandler.hpp>
#include <MessagesToSendManager.hpp>

#include <future>

#include <zmq.hpp>

class Server
{
public:
    Server( ) : 
        ctx( 1 ),
        router( ctx, ZMQ_ROUTER )
    {}

    void run( )
    {
        router.bind( "tcp://*:5570" );
        zmq::message_t identity;
        zmq::message_t msg;

        MessageSender::setRouter( &router );
        std::future<void>( std::async( MessagesToSendManager::safeSenderMethod ) );
        std::future<void>( std::async( RequestHandler::run ) );

        while( true )
        {
            std::cout << "Server waiting for request\n";
            router.recv( &identity );
            router.recv( &msg );

            std::cout << "Server received request\n";
            RequestHandler::newRequest( PersonalMessage( identity, msg ) );
        }
    }

private:
    zmq::context_t ctx;
    zmq::socket_t router;
};

#endif