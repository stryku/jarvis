#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "PersonalMessage.hpp"
#include "RequestHandler.hpp"
#include "MessagesToSendManager.hpp"
#include "log.h"

#include <thread>

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
        LOG( "Server started" );

        router.bind( "tcp://*:5570" );
        zmq::message_t identity;
        zmq::message_t msg;

        MessageSender::setRouter( &router );

        std::thread{ MessageSender::run }.detach();
        std::thread{ MessagesToSendManager::safeSenderMethod }.detach();
        std::thread{ RequestHandler::run }.detach();

        while( true )
        {
            LOG( "Server: waiting for request" );
            router.recv( &identity );
            router.recv( &msg );

            LOG( "Server received request\n" );

            RequestHandler::newRequest( PersonalMessage( identity, msg ) );
        }
    }

private:
    zmq::context_t ctx;
    zmq::socket_t router;
};

#endif
