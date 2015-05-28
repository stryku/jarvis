#include <Task.hpp>

const TaskTypeMap Task::taskTypeMap = TaskTypeMap( );

Task::Task( TaskType type, std::string data ) :
    type( type ),
    data( data )
{}


std::ostream& operator<<( std::ostream &ostream, const Task &task )
{
    ostream << "Task type: " << task.taskTypeMap[task.type] << "\n"
        << "Data:\n" << task.data;

    return ostream;
}