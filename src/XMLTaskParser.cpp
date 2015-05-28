#include <XMLTaskParser.hpp>

TaskTypeMap XMLTaskParser::taskTypeMap = TaskTypeMap( );

TaskType XMLTaskParser::extractTaskType( XMLElement *taskElement )
{
    const char *taskTypeString;

    taskTypeString = taskElement->FirstChildElement( "tasktype" )->GetText( );

    return taskTypeMap[taskTypeString];
}

std::string XMLTaskParser::extractTaskData( XMLElement *taskElement )
{
    const char *taskTypeString;

    taskTypeString = taskElement->FirstChildElement( "taskdata" )->GetText( );

    return std::string( taskTypeString );
}

Task XMLTaskParser::extractTask( const char *xmlData )
{
    XMLDocument doc;
    doc.Parse( xmlData );
    auto taskElement = doc.FirstChildElement();
    TaskType taskType = extractTaskType( taskElement );
    std::string taskData = extractTaskData( taskElement );

    return Task( taskType, taskData );
}

Task XMLTaskParser::extractTask( const std::string &xmlData )
{
    return extractTask( xmlData.c_str( ) );
}