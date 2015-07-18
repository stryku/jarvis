#ifndef BROKER_HPP
#define BROKER_HPP

#include <ThreadSafeQueue.hpp>
#include <ServerRequest.hpp>
#include <log.h>
#include <Semaphore.hpp>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include <future>

#include <zmq.hpp>

class RequestHandler
{
private:
    zmq::socket_t &router;
    ThreadSafeQueue<ServerRequest> queue;

    Semaphore semaphore;

    void handle( const ServerRequest &request ) const
    {

    }

public:
    RequestHandler( zmq::socket_t &router ) :
        router( router ),
        semaphore( 0 )
    {
        std::future<void>( std::async( [this]()
        {
            while( 1 )
            {
                LOG( "[RequestHandler] Waiting for semaphore" );

                semaphore.wait( );
                LOG( "[RequestHandler] semaphore posted" );

                /*std::future<void>( std::async( [this]( )
                {
                    std::cout << "Broker running worker\n";
                    auto req = queue.pop();
                    auto worker = std::make_shared<server_worker>( router, req );
                    worker->work( );
                } ) );*/

            }
        } ) );
    }

    void newRequest( ServerRequest &req )
    {
        LOG( "[BROKER] received msg" );

        queue.push( req );
        semaphore.notify();
    }
};

#endif