#include <Task.hpp>

TaskTypeMap Task::taskTypeMap = TaskTypeMap( );
std::atomic<uint32_t> Task::tasksCount = 0;

Task::Task( TaskType type, std::string data ) :
    type( type ),
    data( data )
{
    assignIdNumber();
    determineIfFast( );
}

