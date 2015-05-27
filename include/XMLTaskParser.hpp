#ifndef _XMLTASKPARSER_HPP_
#define _XMLTASKPARSER_HPP_

#include <string>
#include <map>

#include <tinyxml/tinyxml2.h>

#include <TaskTypeEnum.h>

using namespace tinyxml2;


class XMLTaskParser
{
private:
    static std::map<std::string, TaskType> taskTypeMap;
    static bool mapInitiali

    TaskType extractTaskType( const char *xmlData )
    {
        XMLDocument doc( xmlData );
        XMLElement* taskTypeElement;
        const char *taskTypeString;

        taskTypeElement = doc.FirstChildElement( "tasktype" );
        taskTypeString = taskTypeElement->GetText();

        return taskTypeMap[taskTypeString];
    }

    static

public:
    TaskType taskType;
    std::string taskData;

    XMLTaskParser() {}
    XMLTaskParser( const char *xmlData ) 
    {

        
        
    }

    ~XMLTaskParser() {}



};

#endif // _XMLTASKPARSER_HPP_