#ifndef _VOLUMECHANGERRESULT_HPP_
#define _VOLUMECHANGERRESULT_HPP_

#include <WorkerResult.hpp>

struct VolumeChangerResult : public WorkerResult
{
    bool success;

    VolumeChangerResult( bool success ) :
        success( success )
    {}

    ComplexDataElement toComplexDataElement( )
    {
        return ComplexDataElement( "success", ( success ? "true" : "false" ) );
    }
};

#endif // _VOLUMECHANGERRESULT_HPP_