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
    //std::map<size_t, std::shared_ptr<Task>> ;

    void executeTask( const Task &task )
    {
        //std::cout << task << "\n\n";

        auto subTask = XMLTaskParser::extractTask( task.data.c_str( ) );
        //std::cout << subTask << "\n\n\n";

        subTask.execute();
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