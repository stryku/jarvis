#ifndef _TASKSSTARTED_HPP_
#define _TASKSSTARTED_HPP_

#include <XmlMessage.hpp>
#include <Task.hpp>

class TasksStartedMessage : public XmlMessage
{
protected:
    typedef std::vector<std::shared_ptr<Task>> TasksVec;
    void createDataNode( void *dataPtr )
    {
        TasksVec *tasks;

        /*<task>
            <type>TaskType< / type>
            <id>TaskId< / id>
            <data>TaskData< / data>
            < / task>*/

        tasks = reinterpret_cast<TasksVec*>( dataPtr );

        auto &dataElem = xmlMessageCreator.dataElement;

        for( auto &task : *tasks )
        {
            auto &taskElem = dataElem.newComplexDataElement( "task" );

            taskElem.appendSimpleElement( "type", task->stringType( ) );
            taskElem.appendSimpleElement( "id", task->getIdNumber( ) );
            taskElem.appendSimpleElement( "data", task->data );
        }
    }

private:


public:
    TasksStartedMessage( tcp::socket *socketPtr, void *data ) :
        XmlMessage( XMSG_TASK_RECEIVED, socketPtr )
    {
        createXmlDoc( data );
    };
};


#endif // _TASKSSTARTED_HPP_