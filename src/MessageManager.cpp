#include <MessageManager.hpp>

void MessageManager::receivedNewMessage( const RawMessage message )
{
    std::cout << "[ RECEIVED MESSAGE ]\n" << message.data.data( ) << "\n";

    auto replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASK_RECEIVED );
    sessionPtr->newMessageToSend( replyMessage->toRawMessage( ) );

    auto tasks = XMLTaskParser::extractTasks( message.data.data( ) );

    replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASKS_STARTED, &tasks );
    sessionPtr->newMessageToSend( replyMessage->toRawMessage( ) );

    taskExecutor.execute( tasks );

    replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASKS_FINISHED, &tasks );
    sessionPtr->newMessageToSend( replyMessage->toRawMessage( ) );

    //      
    // execute task - need task executor
}