#ifndef XMLMESSAGEFACTORY_HPP
#define XMLMESSAGEFACTORY_HPP

#include <boost/asio.hpp>

#include <MessageTypeEnum.h>
#include <XmlMessages.h>

using boost::asio::ip::tcp;

class XmlMessageFactory
{
public:
    //static std::shared_ptr<XmlMessage> generateXmlMessage( MessageType type,/*
    //                                                                        tcp::socket *socket,*/
    //                                                                        void *data = nullptr )
    //{
    //    switch( type )
    //    {
    //        case XMSG_TEST: return std::make_shared<TestXmlMessage>( data );
    //        case XMSG_TASK_RECEIVED: return std::make_shared<TaskReceivedMessage>( data );
    //            //case XMSG_TEST: return std::make_shared<TestXmlMessage>( socket, data );
    //            //default:        return std::make_shared<TestXmlMessage>( /*socket,*/ data );
    //            //default:        return std::make_shared<TestXmlMessage>( socket, data );
    //    }
    //}

    static std::shared_ptr<XmlMessage> generateXmlMessage( MessageType type,
                                                           void *data = nullptr )
    {
        switch( type )
        {
            //case XMSG_TEST:             return std::make_shared<TestXmlMessage>( data );
            //case XMSG_TASK_RECEIVED:    return std::make_shared<TaskReceivedMessage>( data );
            //case XMSG_TASKS_STARTED:    return std::make_shared<TasksStartedMessage>( data );
            //case XMSG_TASKS_FINISHED:   return std::make_shared<TasksFinishedMessage>( data );
                //case XMSG_TEST: return std::make_shared<TestXmlMessage>( socket, data );
                //default:        return std::make_shared<TestXmlMessage>( /*socket,*/ data );
                //default:        return std::make_shared<TestXmlMessage>( socket, data );
        }
    }
};

#endif