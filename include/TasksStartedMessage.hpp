#ifndef _TASKSSTARTED_HPP_
#define _TASKSSTARTED_HPP_

#include <XmlMessage.hpp>
#include <Task.hpp>

class TasksStartedMessage : public XmlMessage
{
protected:
    typedef std::shared_ptr<Task> TaskPtr;
    typedef std::vector<TaskPtr> TasksVec;

    void createDataNode( void *dataPtr )
    {
        TasksVec &tasks = *( reinterpret_cast<TasksVec*>( dataPtr ) );

        auto &dataElem = xmlMessageCreator.dataElement;

        for( auto &task : tasks )
        {
            auto &taskElem = dataElem.newComplexXmlElement( "task" );
            //auto 

            taskElem.appendSimpleElement( "type", task->stringType( ) );
            taskElem.appendSimpleElement( "id", task->getIdNumber( ) );
            //taskElem.appendComplexElement( task->result->toComplexXmlElement( ) );
        }
    }

private:


public:
    TasksStartedMessage( void *data ) :
        XmlMessage( XMSG_TASK_RECEIVED )
    {
        createXmlDoc( data );
    };
};


#endif // _TASKSSTARTED_HPP_