#include <Server.hpp>

int main( int argc, char* argv[] )
{
    try
    {
       

        boost::asio::io_service io_service;
        Server s( io_service, 1234 );
        io_service.run( );
    }
    catch( std::exception& e )
    {
        std::cerr << "Exception: " << e.what( ) << "\n";
    }

    return 0;
}