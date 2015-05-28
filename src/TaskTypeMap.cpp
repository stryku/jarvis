#include <TaskTypeMap.hpp>

void TaskTypeMap::addTaskType( const std::string &taskString, TaskType taskType )
{
    //map.insert( ElementPair( taskString, taskType ) );
    map.insert( Map::value_type( taskString, taskType ) );

    //bm_type::value_typeW
}

void TaskTypeMap::init( )
{
    addTaskType( "PC Manage Task", TASK_PC_MANAGE );
    addTaskType( "Jarvis Manage Task", TASK_JARVIS_MANAGE );

    addTaskType( "test", TASK_TEST );
    addTaskType( "change volume", TASK_VOLUME_CHANGE );
}