#ifndef SERVERREQUEST_HPP
#define SERVERREQUEST_HPP

#include <zmq.hpp>

struct PersonalMessage
{
    zmq::message_t identity;
    zmq::message_t msg;

    PersonalMessage( zmq::message_t &identity_, zmq::message_t &msg_ )
    {
        identity.copy( &identity_ );
        msg.copy( &msg_ );
    }

    PersonalMessage( const PersonalMessage &req )
    {
        identity.copy( &req.identity );
        msg.copy( &req.msg );
    }
};
#endif