#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include <queue>
#include <boost/lockfree/queue.hpp>
#include <mutex>

#include <MessageSender.hpp>
#include <XmlMessageFactory.hpp>

#include <iostream>

class MessageManager
{
private:
    typedef std::shared_ptr<RawMessage> MessagePtr;
    typedef std::queue<MessagePtr> MessageQueue;

    std::mutex messagesToSendMutex;
    bool sendingInProgress;

    void sendMessages( )
    {
        if( !sendingInProgress )
        {
            sendingInProgress = true;

            while( !messagesToSend.empty( ) )
            {
                MessagePtr tmp;
                MessageSender::sendMessage( messagesToSend.front() );

                messagesToSendMutex.lock();
                messagesToSend.pop();
                messagesToSendMutex.unlock();

            }

            sendingInProgress = false;
        }
    }

    void newMessageToExecute( const RawMessage &rawMessage )
    {

    }

    //MessageQueue receivedMessages;
    MessageQueue messagesToSend;
    TaskExecutor taskExecutor;


public:
    MessageManager() : 
        sendingInProgress( false ) 
    {}
    ~MessageManager() {}

    void receivedNewMessage( const RawMessage &message )
    {
        std::cout << "[ RECEIVED MESSAGE ]\n" << message.data.data() << "\n";;
        //receivedMessages.push( message );
        auto replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASK_RECEIVED, message.socketPtr );
        // reply that we have received that message - need xml message factory
        newMessageToSend( replyMessage->toRawMessage( ) );
        taskExecutor.execute( message.data.data() );
        //      
        // execute task - need task executor
    }

    void newMessageToSend( std::shared_ptr<RawMessage> &rawMessage )
    {
        messagesToSendMutex.lock();
        messagesToSend.push( rawMessage );
        messagesToSendMutex.unlock();
        sendMessages();
    }

    
};

#endif // MESSAGEMANAGER_HPP