#ifndef _XMLTASKPARSER_HPP_
#define _XMLTASKPARSER_HPP_

#include <string>
#include <vector>

#include <rapidxml\rapidxml.hpp>
#include <rapidxml\rapidxml_print.hpp>

#include <Task.hpp>
#include <TaskTypeMap.hpp>

using namespace rapidxml;

class XMLTaskParser
{
private:
    static TaskTypeMap taskTypeMap;

    static const char* extractChildElementText( const xml_node<> *taskNode,
                                                const char *elementName );
    static TaskType extractTaskType( const xml_node<> *taskNode );
    static std::string extractTaskData( const xml_node<> *taskNode );

public:
    XMLTaskParser() {}
    ~XMLTaskParser() {}

    static std::vector<Task> extractTasks( const char *xmlData );
    static Task extractTask( const xml_node<> *taskNode );
    static Task extractTask( const char *xmlData );
};

#endif // _XMLTASKPARSER_HPP_