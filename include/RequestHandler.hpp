#ifndef BROKER_HPP
#define BROKER_HPP

#include <ThreadSafeQueue.hpp>
#include <PersonalMessage.hpp>
#include <log.h>
#include <XmlMessageParser.hpp>
#include <MessagesToSendManager.hpp>
#include <XmlMessageFactory.hpp>
#include <SimpleXmlParser.hpp>
#include <XMLTaskParser.hpp>
#include <TaskExecutor.hpp>

#include <future>

#include <zmq.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

class RequestHandler
{
private:
    typedef boost::interprocess::interprocess_semaphore Semaphore;
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
        auto id = SimpleXmlParser::extractChildren( "receivedmsgid", msg->data.c_str() );
        MessagesToSendManager::receivedConfim( id );
    }

    static void runTasks( const MessagePtr &msg, const zmq::message_t &identity )
    {
        auto tasks = XMLTaskParser::extractTasks( msg->data.c_str() );

        TaskExecutor::execute( tasks, identity );
    }

    static void handle( const PersonalMessage &request ) 
    {
        auto msg = XmlMessageParser::extract( static_cast<const char*>( request.msg.data() ) );

        LOG( "Handling message:\n" << *msg.get() );

        sendReplyIfNeed( msg, request.identity );

        switch( msg->type )
        {
            case XMSG_RECEIVED: receivedConfimation( msg ); break;
            case XMSG_TASK: runTasks( msg, request.identity ); break;
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