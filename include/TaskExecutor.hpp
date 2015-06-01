#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include <map>

#include <WorkersManager.hpp>
#include <XMLTaskParser.hpp>
#include <RawMessage.hpp>

class TaskExecutor
{
private:
    WorkersManager workersManager;

    void executeTask( const TaskPtr &taskPtr )
    {
        auto subTask = XMLTaskParser::extractTask( taskPtr->data.c_str( ) );
        subTask->execute();
    }

public:
    TaskExecutor( ) {}
    ~TaskExecutor( ) {}

    std::vector<TaskPtr> execute( const char *data )
    {
        auto tasks = XMLTaskParser::extractTasks( data );

        for( const auto &task : tasks )
            executeTask( task );

        return tasks;
    }
};

#endif // _MAINWORKER_HPP_