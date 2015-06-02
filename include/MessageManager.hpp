#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include <queue>
#include <boost/lockfree/queue.hpp>
#include <mutex>

//#include <MessageSender.hpp>
#include <XmlMessageFactory.hpp>

#include <iostream>

#include <Session.hpp>

class MessageManager
{
private:
    typedef std::shared_ptr<Session> SessionPtr;

    TaskExecutor taskExecutor;
    SessionPtr sessionPtr;

public:
    MessageManager( SessionPtr sessionPtr ) :
        sessionPtr( sessionPtr )
    {}
    ~MessageManager() {}

    void receivedNewMessage( const RawMessage message );

    
};

#endif // MESSAGEMANAGER_HPP