#ifndef _VOLUMECHANGERRC_HPP_
#define _VOLUMECHANGERRC_HPP_

#include "WorkerResult.hpp"

class VolumeChangerResult : public WorkerResult
{
public:
    VolumeChangerResult( TaskResultCode resultCode ) :
        WorkerResult( resultCode )
    {}

    ComplexXmlElement toComplexXmlElement( )
    {
        return ComplexXmlElement( "resultcode", stringResultCode() );
    }
};

#endif // _VOLUMECHANGERRC_HPP_
