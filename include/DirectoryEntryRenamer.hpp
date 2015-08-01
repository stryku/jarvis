#pragma once

#include <Worker.hpp>
#include <SimpleXmlParser.hpp>
#include <log.h>
#include <SimpleWorkerResult.hpp> 

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

class DirectoryEntryRenamer : public Worker
{
private:
    typedef boost::filesystem::path Path;
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        Path path;
        Path newPath;
    }workData;

    void extractWorkData( const char *taskData )
    {
        workData.path = SimpleXmlParser::extractChildren( "path", taskData );
        workData.newPath = SimpleXmlParser::extractChildren( "newpath", taskData );
    }

public:
    DirectoryEntryRenamer() {}
    ~DirectoryEntryRenamer() {}

    WorkerResultPtr doWork( const char *data )
    {
        try
        {
            ::Sleep( 3000 );
            std::string taskData( data );

            extractWorkData( taskData.c_str( ) );

            LOG( "Renaming " << workData.path << " to " << workData.newPath );
        
            boost::filesystem::rename( workData.path, workData.newPath );

            return std::make_shared<SimpleWorkerResult>( RC_SUCCESS );
        }
        catch( ... )
        {
            return std::make_shared<SimpleWorkerResult>( RC_FAIL );
        }

        return std::make_shared<SimpleWorkerResult>( RC_FAIL );
    }
};