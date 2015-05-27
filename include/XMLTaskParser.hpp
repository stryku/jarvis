#ifndef _XMLTASKPARSER_HPP_
#define _XMLTASKPARSER_HPP_

#include <string>

#include <tinyxml/tinyxml2.h>

#include <TaskTypeEnum.h>


struct XMLTaskParser
{
    TaskType taskType;
    std::string taskData;

    XMLTaskParser() {}
    XMLTaskParser( const char *xmlData ) 
    {
        XMLDocument doc;

        
    }

    ~XMLTaskParser() {}



};

#endif // _XMLTASKPARSER_HPP_