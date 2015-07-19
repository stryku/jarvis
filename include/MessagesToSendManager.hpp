#ifndef MessagesToSendManager_hpp
#define MessagesToSendManager_hpp

#include <ThreadSafeQueue.hpp>
#include <MessageToSend.hpp>
#include <MessageSender.hpp>
#include <XmlMessage.hpp>

#include <zmq.hpp>
#include <atomic>

class MessagesToSendManager
{
private:
    typedef std::shared_ptr<XmlMessage> XmlMessagePtr;

    static zmq::socket_t *routerSocket;
    static std::atomic<uint64_t> id;

public:
    
    static void quickSend( const XmlMessagePtr &msg, 
                           const zmq::message_t &identity )
    {
        MessageSender::newMessageToSend( PersonalMessage( identity, 
                                                          msg->toZmqMessage() ) );
    }

    static void safeSend( const PersonalMessage &msg, const std::string &msgId )
    {

    }

};

#endif