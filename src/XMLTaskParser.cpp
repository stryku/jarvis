#include <XMLTaskParser.hpp>

TaskTypeMap XMLTaskParser::taskTypeMap = TaskTypeMap( );

TaskType XMLTaskParser::extractTaskType( const xml_node<> *taskNode )
{
    const char *taskTypeString;

    taskTypeString = taskNode->first_node( "tasktype" )->value();

    return taskTypeMap[taskTypeString];
}

std::string XMLTaskParser::extractTaskData( const xml_node<> *taskNode )
{
    auto taskDataNode = taskNode->first_node( "taskdata" );
    std::string ret;

    print( std::back_inserter( ret ), *taskDataNode, 0 );

    return ret;
}

std::vector<TaskPtr> XMLTaskParser::extractTasks( const char *xmlData )
{
    std::vector<TaskPtr> tasks;
    xml_document <> doc;
    doc.parse<0>( const_cast<char*>( xmlData ) );

    for( auto *taskNode = doc.first_node( );
         taskNode;
         taskNode = doc.first_node( ) )
    {
        taskNode = taskNode->last_node();
        TaskType taskType = extractTaskType( taskNode );
        std::string taskData = extractTaskData( taskNode );

        tasks.push_back( std::make_shared<Task>( taskType, taskData ) );

        doc.remove_first_node( );
    }

    return tasks;
}

TaskPtr XMLTaskParser::extractTask( const char *xmlData )
{
    std::vector<Task> tasks;
    xml_document <> doc;
    doc.parse<0>( const_cast<char*>( xmlData ) );
    auto *taskNode = doc.first_node();

    TaskType taskType = extractTaskType( taskNode );
    std::string taskData = extractTaskData( taskNode );

    return std::make_shared<Task>( taskType, taskData );
}

TaskPtr XMLTaskParser::extractTask( const xml_node<> *taskNode )
{
    TaskType taskType = extractTaskType( taskNode );
    std::string taskData = extractTaskData( taskNode );

    return std::make_shared<Task>( taskType, taskData );
}