#ifndef TESTXMLMESSAGE_HPP
#define TESTXMLMESSAGE_HPP

#include <XmlMessage.hpp>

class TestXmlMessage : public XmlMessage
{
protected:
    void createDataNode( void *dataPtr )
    {
        DataStruct data( dataPtr );
        auto dataNode = xmlDoc.allocate_node( node_element, "data" );
        auto someIntString = std::to_string( data.someInt );

        auto someIntNode = xmlDoc.allocate_node( node_element, "someint", someIntString.c_str() );
        auto someCharNode = xmlDoc.allocate_node( node_element, "somechar", &data.someChar, 0, 1 );
        auto someCharArrayNode = xmlDoc.allocate_node( node_element, "somechararray", data.someCharArray );
        
        dataNode->append_node( someIntNode );
        dataNode->append_node( someCharNode );
        dataNode->append_node( someCharArrayNode );

        xmlDoc.first_node()->append_node( dataNode );
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
    TestXmlMessage( void *data ) : XmlMessage( XMSG_TEST )
    {
        createXmlDoc( data );
    };
    TestXmlMessage( tcp::socket *socket, void *data ) :
        XmlMessage( socket )
    {};


    RawMessage toRawMessage()
    {
        RawMessage rawMessage;

        return rawMessage;
    };
};

#endif // TESTXMLMESSAGE_HPP