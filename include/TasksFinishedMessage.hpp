#ifndef _TASKFINISHEDMESSAGE_HPP_
#define _TASKFINISHEDMESSAGE_HPP_


#include <XmlMessage.hpp>
#include <Task.hpp>

class TasksFinishedMessage : public XmlMessage
{
protected:
    typedef std::shared_ptr<Task> TaskPtr;
    typedef std::vector<TaskPtr> TasksVec;
    void createDataNode( void *dataPtr )
    {
        TasksVec *tasks;

        tasks = reinterpret_cast<TasksVec*>( dataPtr );

        auto &dataElem = xmlMessageCreator.dataElement;

        for( auto &task : *tasks )
        {
            auto &taskElem = dataElem.newComplexDataElement( "task" );

            taskElem.appendSimpleElement( "type", task->stringType( ) );
            taskElem.appendSimpleElement( "id", task->getIdNumber( ) );
            taskElem.appendComplexElement( task->result->toComplexDataElement( ) );
        }
    }


public:
    TasksFinishedMessage( void *data ) :
        XmlMessage( XMSG_TASKS_FINISHED )
    {
        createXmlDoc( data );
    };
};

#endif // _TASKFINISHEDMESSAGE_HPP_