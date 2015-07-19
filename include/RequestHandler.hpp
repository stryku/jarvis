#ifndef BROKER_HPP
#define BROKER_HPP

#include <ThreadSafeQueue.hpp>
#include <PersonalMessage.hpp>
#include <log.h>
#include <Semaphore.hpp>
#include <XmlMessageParser.hpp>
#include <MessagesToSendManager.hpp>
#include <XmlMessageFactory.hpp>
#include <SimpleXmlParser.hpp>

#include <future>

#include <zmq.hpp>

class RequestHandler
{
private:
    typedef std::shared_ptr<Message> MessagePtr;

    static ThreadSafeQueue<PersonalMessage> queue;

    static void sendReplyIfNeed( MessagePtr &msg, const zmq::message_t &identity )
    {
        if( msg->needReply )
        {
            auto xmlMessage = XmlMessageFactory::generateXmlMessage( XMSG_RECEIVED, &msg->id );
            MessagesToSendManager::quickSend( xmlMessage, identity );
        }
    }

    static void receivedConfimation( const MessagePtr &msg )
    {
        auto id = SimpleXmlParser::extractNode( "receivedmsgid", msg->data.c_str() );
        MessagesToSendManager::receivedConfim( id );
    }

    static void handle( const PersonalMessage &request ) 
    {
        auto msg = XmlMessageParser::extract( static_cast<const char*>( request.msg.data() ) );

        LOG( "Handling message:\n" << *msg.get() );

        sendReplyIfNeed( msg, request.identity );

        switch( msg->type )
        {
            case XMSG_RECEIVED: receivedConfimation( msg ); break;
        }
    }

public:
    static void run()
    {
        while( 1 )
            handle( queue.pop( ) );
    }

    static void newRequest( PersonalMessage &msg )
    {
        LOG( "Received msg" << std::endl << static_cast<const char*>( msg.msg.data() ) );

        queue.push( msg );
    }
};

ThreadSafeQueue<PersonalMessage> RequestHandler::queue;

#endif