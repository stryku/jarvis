#ifndef MESSAGESENDER_HPP
#define MESSAGESENDER_HPP

#include "ThreadSafeQueue.hpp"
#include "PersonalMessage.hpp"

#include <zmq.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

class MessageSender
{
private:
    typedef boost::interprocess::interprocess_semaphore Semaphore;
    typedef std::unique_ptr<Semaphore> SemaphorePtr;

    static zmq::socket_t *router;
    static ThreadSafeQueue<PersonalMessage> messagesToSend;
    static SemaphorePtr semaphore;

public:
    static void run()
    {
        while( 1 )
        {
            auto msg = messagesToSend.pop();

            router->send( msg.identity, ZMQ_SNDMORE );
            router->send( msg.msg );
        }
    }

    static void newMessageToSend( const PersonalMessage &msg )
    {
        messagesToSend.push( msg );
    }

    static void setRouter( zmq::socket_t *newRouter )
    {
        router = newRouter;
    }
};

zmq::socket_t* MessageSender::router;
ThreadSafeQueue<PersonalMessage> MessageSender::messagesToSend;
MessageSender::SemaphorePtr MessageSender::semaphore = std::make_unique<MessageSender::Semaphore>( 0 );

#endif // MESSAGESENDER_HPP
