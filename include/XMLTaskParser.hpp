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

    static const char* extractChildElementText( XMLElement *taskElement,
                                                const char *elementName );
    static TaskType extractTaskType( XMLElement *taskElement );
    static std::string extractTaskData( XMLElement *taskElement );

public:
    XMLTaskParser() {}
    ~XMLTaskParser() {}

    static Task extractTask( const char *xmlData );
    static Task extractTask( const std::string &xmlData );

};

#endif // _XMLTASKPARSER_HPP_