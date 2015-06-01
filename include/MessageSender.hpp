#ifndef MESSAGESENDER_HPP
#define MESSAGESENDER_HPP

#include <string>
#include <boost/asio.hpp>

#include <RawMessage.hpp>

using boost::asio::ip::tcp;

class MessageSender
{
public:
    static void sendMessage( const RawMessage &message )
    {
        boost::asio::async_write( *( message.socketPtr ),
                                  boost::asio::buffer( message.toStdString( ) ),
                                  []( boost::system::error_code ec, size_t writtenBytesCount ) 
                                  {   
                                      if( !ec )
                                          throw boost::system::system_error( ec );
                                  } );
    }
};

#endif // MESSAGESENDER_HPP