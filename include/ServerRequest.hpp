#ifndef SERVERREQUEST_HPP
#define SERVERREQUEST_HPP

#include <zmq.hpp>

struct ServerRequest
{
    zmq::message_t identity;
    zmq::message_t msg;

    ServerRequest( zmq::message_t &identity_, zmq::message_t &msg_ )
    {
        identity.copy( &identity_ );
        msg.copy( &msg_ );
    }
    ServerRequest( const ServerRequest &req )
    {
        identity.copy( &req.identity );
        msg.copy( &req.msg );
    }
};
#endif