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
        identity.copy( const_cast<zmq::message_t*>( &identity_ ) );
        msg.copy( const_cast<zmq::message_t*>( &msg_ ) );
    }

    PersonalMessage( const zmq::message_t &identity_, const ZmqMessagePtr &msg_ )
    {
        identity.copy( const_cast<zmq::message_t*>( &identity_ ) );
        msg.copy( msg_.get() );
    }

    PersonalMessage( const PersonalMessage &req )
    {
        identity.copy( const_cast<zmq::message_t*>( &req.identity ) );
        msg.copy( const_cast<zmq::message_t*>( &req.msg ) );
    }
};
#endif
