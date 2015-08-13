#pragma once

#include <ComplexXmlElement.hpp>
#include <FolderMemberTypeMap.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

class FolderMember
{
private:
    typedef boost::filesystem::path Path;
    typedef boost::filesystem::directory_entry DirEntry;

    static FolderMemberTypeMap typeMap;

    Path path;
    FolderMemberType type;
    uint64_t size;

public:
    FolderMember( const Path &path ) :
        path( path ) 
    {
        auto dirEntry = DirEntry( path );

        if( boost::filesystem::is_directory( path ) )
        {
            type = FM_FOLDER;
            size = 0;
        }
        else if( boost::filesystem::is_regular_file( path ) )
        {
            type = FM_FILE;
            size = boost::filesystem::file_size( path );
        }
        else
            type = FM_UNDEF;
    }
    ~FolderMember( ) {}

    ComplexXmlElement toComplexXmlElement() const
    {
        ComplexXmlElement element( "member" );

        element.appendSimpleElement( "name", path.filename().string() );
        element.appendSimpleElement( "type", typeMap[type] );
        element.appendSimpleElement( "size", size );

        return element;
    }
};

