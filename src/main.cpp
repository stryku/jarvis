//#include <XmlMessageFactory.hpp>
//#include <fstream>
//#include <string>
//#include <iostream>
//
//struct DataStruct
//{
//    int someInt;
//    char someChar;
//    char someCharArray[20];
//
//    DataStruct() {}
//    DataStruct( void *dataPtr )
//    {
//        *this = reinterpret_cast<DataStruct*>( dataPtr );
//    }
//};
//
//int main( int argc, char* argv[] )
//{
//    DataStruct data;
//
//    data.someInt = 22;
//    data.someChar = 'A';
//    data.someCharArray[0] = 'a';
//    data.someCharArray[1] = 'b';
//    data.someCharArray[2] = 'c';
//    data.someCharArray[3] = '\0';
//
//    auto m = XmlMessageFactory::generateXmlMessage( XMSG_TASK_RECEIVED );
//
//    std::cout << m->toStdString();
//
//    return 0;
//}

#include <Server.hpp>

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

void initEasylogging()
{
    el::Configurations conf( "config/log/log.conf" );
    el::Loggers::reconfigureAllLoggers( conf );
}

int main( int argc, char* argv[] )
{
    try
    {
        initEasylogging();
        char *port;

        if( argc != 2 )
        {
            port = "21020";
        }
        else
            port = argv[1];

        //tcp::endpoint endpoint( tcp::v4( ), std::atoi( port ) );
        //boost::asio::io_service io_service;
        Server s;
        //s.run( );
        s.run( );
    }
    catch( std::exception& e )
    {
        std::cerr << "Exception: " << e.what( ) << "\n";
    }

    return 0;
}