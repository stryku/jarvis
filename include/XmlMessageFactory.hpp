#ifndef XMLMESSAGEFACTORY_HPP
#define XMLMESSAGEFACTORY_HPP

#include <boost/asio.hpp>

#include <MessageTypeEnum.h>
#include <XmlMessages.h>

using boost::asio::ip::tcp;

class XmlMessageFactory
{
public:
    static std::shared_ptr<XmlMessage> generateXmlMessage( MessageType type,
                                          tcp::socket *socket,
                                          void *data )
    {
        switch( type )
        {
            case XMSG_TEST: return std::make_shared<TestXmlMessage>( socket, data );
            default:        return std::make_shared<TestXmlMessage>( socket, data );
        }
    }
};

#endif