#include <XmlMessageCreator.hpp>

void XmlMessageCreator::addType( const std::string &type )
{
    typeString = type;
}
void XmlMessageCreator::addNeedReply( const bool needReply )
{
    needReplyString = ( needReply ? "true" : "false" );
}
void XmlMessageCreator::addId( const std::string &id )
{
    this->id = id;
}

void XmlMessageCreator::createBasicXml( XmlDocument &xmlDoc ) const
{
    auto msg = xmlDoc.allocate_node( node_element, "msg" );
    auto typeNode = xmlDoc.allocate_node( node_element, 
                                          "type", 
                                          typeString.c_str( ) );
    auto needReplyNode = xmlDoc.allocate_node( node_element,
                                               "needreply",
                                               needReplyString.c_str( ) );
    auto idNode = xmlDoc.allocate_node( node_element,
                                        "id",
                                        id.c_str( ) );

    msg->append_node( typeNode );
    msg->append_node( needReplyNode );
    msg->append_node( idNode );

    xmlDoc.append_node( msg );
}

void XmlMessageCreator::createDataElement( XmlDocument &xmlDoc,
                                           XmlNode *dataNode,
                                           const SimpleXmlElement &dataElement ) const
{
    auto dataElementNode = xmlDoc.allocate_node( node_element,
                                                 dataElement.name.c_str( ),
                                                 dataElement.value.c_str( ) );

    dataNode->append_node( dataElementNode );
}

void XmlMessageCreator::createDataNode( XmlDocument &xmlDoc ) const
{
    auto dataNode = dataElement.toXmlNode( xmlDoc );

    xmlDoc.first_node()->append_node( dataNode );
}

std::string XmlMessageCreator::toStdString( ) const
{
    std::string ret;
    XmlDocument xmlDoc;

    createBasicXml( xmlDoc );
    createDataNode( xmlDoc );

    print( std::back_inserter( ret ), xmlDoc, 0 );

    return ret;
}