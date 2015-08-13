#ifndef _TASKFINISHEDMESSAGE_HPP_
#define _TASKFINISHEDMESSAGE_HPP_


#include <XmlNeedReplyMessage.hpp>
#include <Task.hpp>

class TaskFinishedMessage : public XmlNeedReplyMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        Task &task = *( reinterpret_cast<Task*>( dataPtr ) );

        auto &dataElem = xmlMessageCreator.dataElement;
        auto &taskElem = dataElem.newComplexXmlElement( "result" );

        dataElem.appendSimpleElement( "taskid", task.stringType() );
        taskElem.appendComplexElement( task.result->toComplexXmlElement() );

/*
        taskElem.appendSimpleElement( "type", task->stringType( ) );
        taskElem.appendSimpleElement( "id", task->getIdNumber( ) );
        taskElem.appendComplexElement( task->result->toComplexXmlElement( ) );*/
    }


public:
    TaskFinishedMessage( void *data ) :
        XmlNeedReplyMessage( XMSG_TASK_FINISHED )
    {
        createXmlDoc( data );
    };
};

#endif // _TASKFINISHEDMESSAGE_HPP_