#include <Task.hpp>

TaskTypeMap Task::taskTypeMap = TaskTypeMap( );
uint32_t Task::tasksCount = 0;
std::mutex Task::taskCountMutex;

Task::Task( TaskType type, std::string data ) :
    type( type ),
    data( data )
{
    assignIdNumber();
}

