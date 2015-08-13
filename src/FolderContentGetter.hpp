#pragma once

#include "Worker.hpp"
#include "SimpleXmlParser.hpp"
#include "log.h"
#include "FolderMember.hpp"
#include "FolderContentGetterResult.hpp"

#include <algorithm>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

class FolderContentGetter : public Worker
{
private:
    typedef boost::filesystem::path Path;
    typedef boost::filesystem::directory_iterator DirIterator;
    typedef std::vector<FolderMember> Members;
    typedef std::shared_ptr<WorkerResult> WorkerResultPtr;

    struct WorkData
    {
        Path path;
    }workData;

    void extractWorkData( const char *taskData )
    {
        auto data = SimpleXmlParser::extractChildren( "path", taskData );

        workData.path = Path( data );
    }

    void getMembers( Path &path, Members &members )
    {
        std::vector<Path> paths;

        std::copy( DirIterator( path ), DirIterator( ), std::back_inserter( paths ) );

        for( const auto &i : paths )
            members.push_back( FolderMember( i ) );
    }

public:
    FolderContentGetter() {}
    ~FolderContentGetter() {}

    WorkerResultPtr doWork( const char *data )
    {
        std::string taskData( data );
        Members members;

        extractWorkData( taskData.c_str( ) );

        LOG( "Getting members from " << workData.path );

        try
        {
            getMembers( workData.path, members );
            return std::make_shared<FolderContentGetterResult>( RC_SUCCESS, members );
        }
        catch( ... )
        {
            return std::make_shared<FolderContentGetterResult>( RC_FAIL, Members( ) );
        }

        return std::make_shared<FolderContentGetterResult>( RC_FAIL, Members( ) );
    }
};
