#ifndef MESSAGESENDER_HPP
#define MESSAGESENDER_HPP

#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class MessageSender
{
public:
    static void sendMessage( tcp::socket &socket,
                             const std::string &message )
    {
        boost::asio::async_write( socket,
                                  boost::asio::buffer( message.c_str(), message.size() ),
                                  []( boost::system::error_code ec ) 
                                  {   
                                      if( !ec )
                                          throw boost::system::system_error( ec );
                                  } );
    }
};

#endif // MESSAGESENDER_HPP