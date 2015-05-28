#include <XMLTaskParser.hpp>

TaskTypeMap XMLTaskParser::taskTypeMap = TaskTypeMap( );

TaskType XMLTaskParser::extractTaskType( xml_node<> *taskNode )
{
    const char *taskTypeString;

    taskTypeString = taskNode->first_node( "tasktype" )->value();

    return taskTypeMap[taskTypeString];
}

#include <iostream>
#include <string>
#include <rapidxml\rapidxml_print.hpp>

std::string XMLTaskParser::extractTaskData( xml_node<> *taskNode )
{
    auto taskDataNode = taskNode->first_node( "taskdata" );
    std::string ret;

    print( std::back_inserter( ret ), *taskDataNode, 0 );

    return ret;
}

Task XMLTaskParser::extractTask( const char *xmlData )
{
    xml_document <> doc;
    doc.parse<0>( const_cast<char*>( xmlData ) );

    auto taskElement = doc.first_node();
    TaskType taskType = extractTaskType( taskElement );
    std::string taskData = extractTaskData( taskElement );

    return Task( taskType, taskData );
}

Task XMLTaskParser::extractTask( const std::string &xmlData )
{
    return extractTask( xmlData.c_str( ) );
}