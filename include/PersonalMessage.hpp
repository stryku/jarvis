#ifndef SERVERREQUEST_HPP
#define SERVERREQUEST_HPP

#include <memory>

#include <zmq.hpp>

struct PersonalMessage
{
    typedef std::shared_ptr<zmq::message_t> ZmqMessagePtr;

    zmq::message_t identity;
    zmq::message_t msg;

    PersonalMessage( const zmq::message_t &identity_, const zmq::message_t &msg_ )
    {
        identity.copy( &identity_ );
        msg.copy( &msg_ );
    }

    PersonalMessage( const zmq::message_t &identity_, const ZmqMessagePtr &msg_ )
    {
        identity.copy( &identity_ );
        msg.copy( msg_.get() );
    }

    PersonalMessage( const PersonalMessage &req )
    {
        identity.copy( &req.identity );
        msg.copy( &req.msg );
    }
};
#endif