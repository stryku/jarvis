#ifndef TESTXMLMESSAGE_HPP
#define TESTXMLMESSAGE_HPP

#include <XmlMessage.hpp>

class TestXmlMessage : public XmlMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        DataStruct data( dataPtr );

        auto &dataElem = xmlMessageCreator.dataElement;

        dataElem.appendSimpleElement( "someint", data.someInt );
        dataElem.appendSimpleElement( "somechar", data.someChar );
        dataElem.appendSimpleElement( "somechararray", data.someCharArray );
    }

private:
    struct DataStruct
    {
        int someInt;
        char someChar;
        char someCharArray[20];

        DataStruct( void *dataPtr )
        {
            *this = *( reinterpret_cast<DataStruct*>( dataPtr ) );
        }
    };


public:
    TestXmlMessage( const TestXmlMessage &message ) :
        XmlMessage( XMSG_TEST, message.socketPtr )
    {
        xmlMessageCreator = message.xmlMessageCreator;
    }
    TestXmlMessage( tcp::socket *socketPtr, void *data ) : 
        XmlMessage( XMSG_TEST, socketPtr )
    {
        createXmlDoc( data );
    };
};

#endif // TESTXMLMESSAGE_HPP