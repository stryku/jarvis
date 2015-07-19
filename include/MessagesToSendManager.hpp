#ifndef MessagesToSendManager_hpp
#define MessagesToSendManager_hpp

#include <ThreadSafeHeap.hpp>
#include <MessageToSend.hpp>
#include <MessageSender.hpp>
#include <XmlMessage.hpp>

#include <zmq.hpp>
#include <atomic>
#include <chrono>
#include <thread>

class MessagesToSendManager
{
private:
    struct SafeMessage;
    typedef std::shared_ptr<SafeMessage> SafeMessagePtr;
    typedef std::shared_ptr<XmlMessage> XmlMessagePtr;
    typedef std::shared_ptr<PersonalMessage> PersonalMessagePtr;

    struct SafeMessage
    {
        PersonalMessagePtr msg;
        std::string id;
        std::chrono::time_point<std::chrono::system_clock> nextTry;

        SafeMessage( const PersonalMessage &personalMsg,
                     const std::string &id ) :
            msg( std::make_shared<PersonalMessage>(personalMsg)),
            id(id)
        {
            static const std::chrono::milliseconds defNextTryDelay( 5000 );
            nextTry = std::chrono::system_clock::now() + defNextTryDelay;
        }

        bool operator<( const SafeMessage &other ) const
        {
            return nextTry > other.nextTry;
        }
    };

    static ThreadSafeHeap<SafeMessagePtr> safeMessages;
    static ThreadSafeQueue<std::string> confirmedMessages;

    static bool wasConfirmed( const std::string &id )
    {
        return confirmedMessages.isInside( id );
    }

public:
    static void safeSenderMethod()
    {
        static const std::chrono::milliseconds defNextTryDelay( 5000 );

        while( 1 )
        {
            auto msg = safeMessages.pop();
            
            auto now = std::chrono::system_clock::now();

            if( now < msg->nextTry )
            {
                auto needToSleep = msg->nextTry - now;
                std::this_thread::sleep_for( needToSleep );
            }

            if( wasConfirmed( msg->id ) )
                confirmedMessages.erase( msg->id );
            else
            {   
                msg->nextTry = std::chrono::system_clock::now( ) + defNextTryDelay;

                MessageSender::newMessageToSend( *msg->msg.get( ) );

                safeMessages.push( msg );
            }
        }
    }

    static void quickSend( const XmlMessagePtr &msg, 
                           const zmq::message_t &identity )
    {
        MessageSender::newMessageToSend( PersonalMessage( identity, 
                                                          msg->toZmqMessage() ) );
    }

    static void safeSend( const MessageToSend &msg )
    {
        MessageSender::newMessageToSend( msg.personalMsg );

        safeMessages.push( std::make_shared<SafeMessage>( msg.personalMsg, 
                                                          msg.id ) );
    }
};

ThreadSafeHeap<MessagesToSendManager::SafeMessagePtr> MessagesToSendManager::safeMessages;
ThreadSafeQueue<std::string> MessagesToSendManager::confirmedMessages;

#endif