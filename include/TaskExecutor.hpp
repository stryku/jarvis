#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include <map>

//#include <WorkersManager.hpp>
#include <XMLTaskParser.hpp>
#include <RawMessage.hpp>

class TaskExecutor
{
private:
    //WorkersManager workersManager;

    void executeTask( const TaskPtr &taskPtr )
    {
        auto subTask = XMLTaskParser::extractTask( taskPtr->data.c_str( ) );
        subTask->execute();
    }

public:
    TaskExecutor( ) {}
    ~TaskExecutor( ) {}

    void execute( std::vector<TaskPtr> &tasks )
    {
        for( const auto &task : tasks )
            task->execute();
    }
};

#endif // _MAINWORKER_HPP_