#include <TaskTypeMap.hpp>

void TaskTypeMap::init( )
{
    add( "TASK_PC_MANAGE", TASK_PC_MANAGE );
    add( "TASK_JARVIS_MANAGE", TASK_JARVIS_MANAGE );

    add( "TASK_VOLUME_CHANGE", TASK_VOLUME_CHANGE );
    add( "TASK_GET_FOLDER_CONTENT", TASK_GET_FOLDER_CONTENT );
    add( "TASK_RENAME_DIR_ENTRY", TASK_RENAME_DIR_ENTRY );
    add( "TASK_INPUT_EVENTS", TASK_INPUT_EVENTS );
}
