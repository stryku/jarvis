#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <ServerRequest.hpp>
#include <RequestHandler.hpp>

#include <zmq.hpp>

class Server
{
public:
    Server( ) : 
        ctx( 1 ),
        router( ctx, ZMQ_ROUTER ),
        requestHandler( router )
    {}

    void run( )
    {
        router.bind( "tcp://*:5570" );
        zmq::message_t identity;
        zmq::message_t msg;

        while( true )
        {
            std::cout << "Server waiting for request\n";
            router.recv( &identity );
            router.recv( &msg );

            std::cout << "Server received request\n";
            requestHandler.newRequest( ServerRequest( identity, msg ) );
        }
    }

private:
    zmq::context_t ctx;
    zmq::socket_t router;
    RequestHandler requestHandler;
};

#endif