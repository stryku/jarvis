#ifndef _XMLTASKPARSER_HPP_
#define _XMLTASKPARSER_HPP_

#include "Task.hpp"
#include "TaskTypeMap.hpp"

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <string>
#include <vector>
#include <memory>

typedef std::shared_ptr<Task> TaskPtr;
using namespace rapidxml;

class XMLTaskParser
{
private:

    static TaskTypeMap taskTypeMap;

    static const char* extractChildElementText( const xml_node<> *taskNode,
                                                const char *elementName );
    static TaskType extractTaskType( const xml_node<> *taskNode );
    static std::string extractTaskData( const xml_node<> *taskNode );
    static std::string extractTaskId( const xml_node<> *taskNode );

public:
    XMLTaskParser() {}
    ~XMLTaskParser() {}

    static std::vector<TaskPtr> extractTasks( const char *xmlData );
    static TaskPtr extractTask( const xml_node<> *taskNode );
    static TaskPtr extractTask( const char *xmlData );
};

#endif // _XMLTASKPARSER_HPP_
