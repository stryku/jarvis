#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <boost/asio.hpp>
//#include <MessageManager.hpp>
#include <XMLTaskParser.hpp>
#include <TaskExecutor.hpp>

using boost::asio::ip::tcp;

class Session :
    public std::enable_shared_from_this<Session>
{
private:
    typedef std::queue<RawMessage> MessageQueue;
    static const size_t messageLengthBuffSize = 20;

    tcp::socket socket_;
    char messageLengthBuff[messageLengthBuffSize];
    RawMessage receivedMessage;
    MessageQueue messagesToSend;
    //MessageManager messageManager;
    TaskExecutor taskExecutor;
    
public:
    Session( tcp::socket socket ) :
        socket_( std::move( socket ) )/*,
        messageManager( shared_from_this() )*/
    {}
    ~Session( ) {}

    void start( )
    {
        readMessageLength();
    }

    void readMessageLength()
    {
        boost::asio::async_read( socket_,
                                 boost::asio::buffer( messageLengthBuff, messageLengthBuffSize ),
                                 [this]( boost::system::error_code ec, std::size_t )
        {
            if( !ec )
            {
                receivedMessage.length = atoi( messageLengthBuff );
                readMessage();
            }
        } );
    }

    void readMessage( )
    {
        boost::system::error_code errorCode;
        bool extractedSize = false;
        size_t readedSize = 0;
        int32_t messageLength;

        boost::asio::async_read( socket_,
                                 boost::asio::buffer( receivedMessage.data, receivedMessage.length ),
                                 [this]( boost::system::error_code ec, std::size_t /*length*/ )
        {
            if( !ec )
            {
                receivedMessage.data[receivedMessage.length] = '\0';
                std::cout << "[ RECEIVED MESSAGE ]\n" << receivedMessage.data.data( ) << "\n";

                auto replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASK_RECEIVED );
                newMessageToSend( replyMessage->toRawMessage( ) );

                auto tasks = XMLTaskParser::extractTasks( receivedMessage.data.data( ) );

                replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASKS_STARTED, &tasks );
                newMessageToSend( replyMessage->toRawMessage( ) );

                taskExecutor.execute( tasks );

                replyMessage = XmlMessageFactory::generateXmlMessage( XMSG_TASKS_FINISHED, &tasks );
                newMessageToSend( replyMessage->toRawMessage( ) );
                readMessageLength();
            }
        } );
    }

    void newMessageToSend( const RawMessage& msg )
    {
        bool write_in_progress = !messagesToSend.empty( );
        messagesToSend.push( msg );
        if( !write_in_progress )
        {
            do_write( );
        }
    }

    void do_write( )
    {
        boost::asio::async_write( socket_,
                                  boost::asio::buffer( messagesToSend.front().data,
                                  messagesToSend.front( ).length ),
                                  [this]( boost::system::error_code ec, std::size_t /*length*/ )
        {
            if( !ec )
            {
                std::cout << "[ SEND ]\n" << messagesToSend.front().data.data() << "\n\n";
                messagesToSend.pop();
                if( !messagesToSend.empty( ) )
                {
                    do_write( );
                }
            }
        } );
    }
};

#endif