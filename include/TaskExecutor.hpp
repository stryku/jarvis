#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include <WorkersManager.hpp>
#include <XMLTaskParser.hpp>

class TaskExecutor
{
private:
    WorkersManager workersManager;

    void executeTask( const Task &task )
    {
        //std::cout << task << "\n\n";

        auto subTask = XMLTaskParser::extractTask( task.data.c_str( ) );
        //std::cout << subTask << "\n\n\n";

        workersManager.doWork( subTask.type, subTask.data );
    }

public:
    TaskExecutor( ) {}
    ~TaskExecutor( ) {}

    void execute( const char *data )
    {
        auto tasks = XMLTaskParser::extractTasks( data );

        for( const auto &task : tasks )
            executeTask( task );
    }
};

#endif // _MAINWORKER_HPP_