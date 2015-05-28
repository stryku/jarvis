#ifndef _XMLTASKPARSER_HPP_
#define _XMLTASKPARSER_HPP_

#include <rapidxml\rapidxml.hpp>

#include <Task.hpp>
#include <TaskTypeMap.hpp>

using namespace rapidxml;

class XMLTaskParser
{
private:
    static TaskTypeMap taskTypeMap;

    static const char* extractChildElementText( xml_node<> *taskNode,
                                                const char *elementName );
    static TaskType extractTaskType( xml_node<> *taskNode );
    static std::string extractTaskData( xml_node<> *taskNode );

public:
    XMLTaskParser() {}
    ~XMLTaskParser() {}

    static Task extractTask( const char *xmlData );
    static Task extractTask( const std::string &xmlData );

};

#endif // _XMLTASKPARSER_HPP_