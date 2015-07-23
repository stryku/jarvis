#pragma once

#include <WorkerResult.hpp>

#include <string>

class DirectoryEntryRenamerResult : public WorkerResult
{
private:
    std::string taskId;

public:
    DirectoryEntryRenamerResult( const TaskResultCode resultCode ) :
        WorkerResult( resultCode ),
        taskId( taskId )
    {}

    ComplexXmlElement toComplexXmlElement( )
    {
        return ComplexXmlElement( "results", stringResultCode() );
    }
};
