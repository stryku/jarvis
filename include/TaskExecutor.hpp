#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include <XMLTaskParser.hpp>
#include <MessagesToSendManager.hpp>

#include <map>

#include <zmq.hpp>

//#include <WorkersManager.hpp>

class TaskExecutor
{
private:
    //WorkersManager workersManager;

    static void sendResult( const TaskPtr &taskPtr, const zmq::message_t &identity )
    {
        auto msg = XmlMessageFactory::generateXmlMessage( XMSG_RESULT,
                                                          taskPtr.get() );

        MessagesToSendManager::safeSend( MessageToSend( msg->getId(), 
                                                        msg.get(),
                                                        identity ) );

    }

    static void executeTask( const TaskPtr &taskPtr, const zmq::message_t &identity )
    {
        /*auto subTask = XMLTaskParser::extractTask( taskPtr->data.c_str( ) );
        subTask->execute();*/
        if( taskPtr->fastTask )
        {
            taskPtr->execute();
            sendResult( taskPtr, identity );
        }

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