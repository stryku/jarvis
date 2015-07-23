#pragma once

#include <WorkerResult.hpp>
#include <FolderMember.hpp>

#include <string>
#include <vector>

#include <boost/filesystem/path.hpp>

struct FolderContentGetterResult : public WorkerResult
{
private:
    typedef std::vector<FolderMember> Members;

public:
    bool success;
    Members members;
    std::string taskId;

    FolderContentGetterResult( bool success, const Members &members ) :
        success( success ),
        members( members ),
        taskId( taskId )
    {}

    ComplexXmlElement toComplexXmlElement( )
    {
        ComplexXmlElement dataElement( "results" );
        ComplexXmlElement membersElement( "members" );

        dataElement.appendSimpleElement( "success", ( success ? "true" : "false" ) );

        for( const auto &member : members )
            membersElement.appendComplexElement( member.toComplexXmlElement() );

        dataElement.appendComplexElement( membersElement );

        return dataElement;
    }
};
