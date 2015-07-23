#pragma once

#include <string>

#include <ConstMap.hpp>
#include <FolderMemberType.h>

class FolderMemberTypeMap : public ConstMap<const std::string, FolderMemberType>
{
private:
    void init( );

public:
    FolderMemberTypeMap( ) { init( ); }
    ~FolderMemberTypeMap( ) {}
};