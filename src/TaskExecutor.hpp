#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include "XMLTaskParser.hpp"
#include "MessagesToSendManager.hpp"

#include <map>
#include <functional>

#include <zmq.hpp>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

//#include <WorkersManager.hpp>



class TaskExecutor
{
private:
    typedef boost::interprocess::interprocess_semaphore Semaphore;

    static void sendResult( const TaskPtr &taskPtr, const zmq::message_t &identity )
    {
        auto msg = XmlMessageFactory::generateXmlMessage( XMSG_RESULT,
                                                          taskPtr.get() );

        MessagesToSendManager::safeSend( MessageToSend( msg->getId(), 
                                                        msg.get(),
                                                        identity ) );

    }

    //static std::shared_ptr<void> getCopiedMsgData( const zmq::message_t &msg )
    //{
    //    auto deleter = []( char *p ) { delete[] p; };
    //    size_t msgSize = msg.size();
    //    auto ptr = new char[msgSize];

    //    std::memcpy( ptr, msg.data(), msgSize );

    //    //std::shared_ptr<char>( new char[10], std::default_delete<char[]>() );
    //    //std::shared_ptr<char> sp( new char[msgSize], array_deleter<char>( ) );
    //}

    static void startTaskThread( const TaskPtr &taskPtr, zmq::message_t &id )
    {
        Semaphore semaphore( 0 );

        auto threadFunction = [&semaphore]( const TaskPtr taskPtr,
                                  zmq::message_t &_id )->void
                              {
                                  zmq::message_t id;
                                  id.copy( &_id );

                                  semaphore.post();

                                  taskPtr->execute();
                                  sendResult( taskPtr, id );
                              };

        std::thread thread( threadFunction, taskPtr, std::ref( id ) );

        semaphore.wait();

        thread.detach();
    }

    static void executeTask( const TaskPtr &taskPtr, const zmq::message_t &id )
    {
        if( taskPtr->fastTask )
        {
            taskPtr->execute();
            sendResult( taskPtr, id );
        }
        else
            startTaskThread( taskPtr, const_cast<zmq::message_t &>( id ) );
    }

public:
    TaskExecutor() {}
    ~TaskExecutor() {}

    static void execute( const std::vector<TaskPtr> &tasks, const zmq::message_t &identity )
    {
        for( const auto &task : tasks )
            executeTask( task, identity );
    }
};

#endif // _MAINWORKER_HPP_
