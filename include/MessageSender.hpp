#ifndef MESSAGESENDER_HPP
#define MESSAGESENDER_HPP

#include <ThreadSafeQueue.hpp>
#include <PersonalMessage.hpp>
#include <Semaphore.hpp>

#include <zmq.hpp>

class MessageSender
{
private:
    static zmq::socket_t *router;
    static ThreadSafeQueue<PersonalMessage> messagesToSend;
    static Semaphore semaphore;

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
Semaphore MessageSender::semaphore;

#endif // MESSAGESENDER_HPP