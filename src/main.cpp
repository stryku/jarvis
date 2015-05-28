#include <TaskExecutor.hpp>
#include <fstream>
#include <string>

int main( int argc, char* argv[] )
{
    TaskExecutor task;
    std::ifstream t( "C:/moje/programowanie/c++/Jarvis/files/test.xml" );
    std::string str( ( std::istreambuf_iterator<char>( t ) ),
                     std::istreambuf_iterator<char>( ) );

    task.execute( str.c_str() );

    return 0;
}