#pragma once

#include "ConstMap.hpp"
#include "FolderMemberType.h"

#include <string>

class FolderMemberTypeMap : public ConstMap<std::string, FolderMemberType>
{
private:
    void init( );

public:
    FolderMemberTypeMap( ) { init( ); }
    ~FolderMemberTypeMap( ) {}
};
