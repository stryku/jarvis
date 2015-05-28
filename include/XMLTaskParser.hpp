#ifndef _XMLTASKPARSER_HPP_
#define _XMLTASKPARSER_HPP_

#include <tinyxml/tinyxml2.h>

#include <Task.hpp>
#include <TaskTypeMap.hpp>

using namespace tinyxml2;

class XMLTaskParser
{
private:
    static TaskTypeMap taskTypeMap;

    static const char* extractElementText( const char *xmlData, const char *elementName )
    {
        XMLDocument doc( xmlData );

        return doc.FirstChildElement( elementName )->GetText();
    }

    static TaskType extractTaskType( const char *xmlData )
    {
        const char *taskTypeString;

        taskTypeString = extractElementText( xmlData, "tasktype" );

        return taskTypeMap[ taskTypeString ];
    }

    static std::string extractTaskData( const char *xmlData )
    {
        const char *taskTypeString;

        taskTypeString = extractElementText( xmlData, "taskdata" );

        return std::string( taskTypeString );
    }

public:
    XMLTaskParser() {}
    ~XMLTaskParser() {}

    static Task extractTask( const char *xmlData )
    {
        const char *taskText = extractElementText( xmlData, "task" );
        TaskType taskType = extractTaskType( taskText );
        std::string taskData = extractTaskData( taskText );

        return Task( taskType, taskData );
    }

    static Task extractTask( const std::string &xmlData )
    {
        return extractTask( xmlData.c_str( ) );
    }

};

#endif // _XMLTASKPARSER_HPP_