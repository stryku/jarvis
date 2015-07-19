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
            semaphore.wait();
            auto msg = messagesToSend.pop();

            router->send( msg.identity );
            router->send( msg.msg );
        }
    }

    static void newMessageToSend( const PersonalMessage &msg )
    {
        messagesToSend.push( msg );
        semaphore.notify();
    }
};

#endif // MESSAGESENDER_HPP