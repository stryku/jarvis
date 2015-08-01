#pragma once

#include <WorkerResult.hpp>
#include <FolderMember.hpp>

#include <string>
#include <vector>

#include <boost/filesystem/path.hpp>

class FolderContentGetterResult : public WorkerResult
{
private:
    typedef std::vector<FolderMember> Members;

    Members members;

public:
    FolderContentGetterResult( const TaskResultCode resultCode,
                               const Members &members ) :
        WorkerResult( resultCode ), 
        members( members )
    {}

    ComplexXmlElement toComplexXmlElement()
    {
        ComplexXmlElement dataElement( "results" );
        ComplexXmlElement membersElement( "members" );

        dataElement.appendSimpleElement( "resultcode", stringResultCode( ) );

        for( const auto &member : members )
            membersElement.appendComplexElement( member.toComplexXmlElement() );

        dataElement.appendComplexElement( membersElement );

        return dataElement;
    }
};
