//#include <TaskExecutor.hpp>
//#include <fstream>
//#include <string>
//
//int main( int argc, char* argv[] )
//{
//    TaskExecutor task;
//    std::ifstream t( "C:/moje/programowanie/c++/Jarvis/files/test.xml" );
//    std::string str( ( std::istreambuf_iterator<char>( t ) ),
//                     std::istreambuf_iterator<char>( ) );
//
//    task.execute( str.c_str() );
//
//    return 0;
//}
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <boost/asio.hpp>

#include <Server.hpp>

using boost::asio::ip::tcp;

int main( int argc, char* argv[] )
{
    try
    {
        char *port;

        if( argc != 2 )
        {
            port = "21020";
        }
        else
            port = argv[1];

        boost::asio::io_service io_service;
        Server s( io_service, std::atoi( port ) );
        io_service.run( );
    }
    catch( std::exception& e )
    {
        std::cerr << "Exception: " << e.what( ) << "\n";
    }

    return 0;
}