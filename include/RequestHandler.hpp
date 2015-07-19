#ifndef BROKER_HPP
#define BROKER_HPP

#include <ThreadSafeQueue.hpp>
#include <PersonalMessage.hpp>
#include <log.h>
#include <Semaphore.hpp>
#include <XmlMessageParser.hpp>
#include <MessagesToSendManager.hpp>
#include <XmlMessageFactory.hpp>

#include <future>

#include <zmq.hpp>

class RequestHandler
{
private:
    typedef std::shared_ptr<Message> MessagePtr;

    zmq::socket_t &router;
    ThreadSafeQueue<PersonalMessage> queue;

    Semaphore semaphore;

    void sendReplyIfNeed( MessagePtr &msg, const zmq::message_t &identity )
    {
        if( msg->needReply )
        {
            auto xmlMessage = XmlMessageFactory::generateXmlMessage( XMSG_RECEIVED, &msg->id );
            MessagesToSendManager::quickSend( xmlMessage, identity );
        }
    }

    void handle( const PersonalMessage &request ) const
    {
        auto msg = XmlMessageParser::extract( static_cast<const char*>( request.msg.data() ) );
    }

public:
    RequestHandler( zmq::socket_t &router ) :
        router( router ),
        semaphore( 0 )
    {
        std::future<void>( std::async( [this]()
        {
            while( 1 )
            {
                LOG( "[RequestHandler] Waiting for semaphore" );

                semaphore.wait( );
                LOG( "[RequestHandler] semaphore posted" );

                /*std::future<void>( std::async( [this]( )
                {
                    std::cout << "Broker running worker\n";
                    auto req = queue.pop();
                    auto worker = std::make_shared<server_worker>( router, req );
                    worker->work( );
                } ) );*/

            }
        } ) );
    }

    void newRequest( PersonalMessage &msg )
    {
        LOG( "[BROKER] received msg" );

        queue.push( msg );
        semaphore.notify();
    }
};

#endif