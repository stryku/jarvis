#ifndef _TESTWORKERRESULT_HPP_
#define _TESTWORKERRESULT_HPP_

#include <WorkerResult.hpp>

struct TestWorkerResult : public WorkerResult
{
    bool success;

    TestWorkerResult( bool success ) :
        success( success )
    {}

    ComplexXmlElement toComplexXmlElement( )
    {
        return ComplexXmlElement( "success", ( success ? "true" : "false" ) );
    }
};

#endif // _VOLUMECHANGERRESULT_HPP_