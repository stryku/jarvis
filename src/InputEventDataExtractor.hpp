#pragma once

#include "SimpleXmlParser.hpp"
#include "Point2d.hpp"

class InputEventDataExtractor
{
    public:
        static int kbKey( const std::string &eventDataInXml )
        {
            auto kbKeyStr = SimpleXmlParser::extractChildrenValue( "key", 
                                                                   eventDataInXml.c_str() );

            return static_cast<int>( kbKeyStr[0] );
        }

        static Point2d<size_t> newMouseCoord( const std::string &eventDataInXml )
        {
            Point2d<size_t> point;
            std::string strX, strY;

            strX = SimpleXmlParser::extractChildren( "x", 
                                                     eventDataInXml.c_str() );
            strY = SimpleXmlParser::extractChildren( "y", 
                                                     eventDataInXml.c_str() );

            //todo zmiana przy zmianie 
            point.x = std::atoi( strX.c_str() );
            point.y = std::atoi( strY.c_str() );

            return point;
        }
};
