#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include <WorkersManager.hpp>
#include <XMLTaskParser.hpp>

class TaskExecutor
{
private:
    //WorkersManager workersManager;

public:
    TaskExecutor( ) {}
    ~TaskExecutor( ) {}

    void execute( const char *data )
    {
        Task mainTask = XMLTaskParser::extractTask( data );

        std::cout << mainTask << "\n";

        auto task = XMLTaskParser::extractTask( mainTask.data );
        std::cout << task << "\n";

        //workersManager.doWork( task.type, task.data );
    }
};

#endif // _MAINWORKER_HPP_