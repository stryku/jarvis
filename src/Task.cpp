#include "Task.hpp"

TaskTypeMap Task::taskTypeMap = TaskTypeMap( );
std::size_t Task::tasksCount = 0;

Task::Task( TaskType type, std::string data, std::string id ) :
    type( type ),
    data( data ),
    id( id )
{
    assignIdNumber();
    determineIfFast( );
}

