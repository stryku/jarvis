#pragma once

#include "XmlNeedReplyMessage.hpp"
#include "WorkerResult.hpp"

class TaskResultsMessage : public XmlNeedReplyMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        auto task = reinterpret_cast<Task*>( dataPtr );

        auto &workerResult = task->result;
        auto &id = task->id;

        auto &dataElem = xmlMessageCreator.dataElement;

        dataElem.appendSimpleElement( "taskid", id );
        dataElem.appendComplexElement( workerResult->toComplexXmlElement( ) );
    }


public:
    TaskResultsMessage( void *data ) :
        XmlNeedReplyMessage( XMSG_RESULT )
    {
        createXmlDoc( data );
    };
};
