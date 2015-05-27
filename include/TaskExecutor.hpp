#ifndef _MAINWORKER_HPP_
#define _MAINWORKER_HPP_

#include <WorkersManager.hpp>
#include <XMLTaskParser.hpp>

class TaskExecutor
{
private:
    WorkersManager workersManager;

public:
    TaskExecutor( ) {}
    ~TaskExecutor( ) {}

    void execute( char *data )
    {

    }
};

#endif // _MAINWORKER_HPP_