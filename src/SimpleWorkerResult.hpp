#pragma once

#include "WorkerResult.hpp"

#include <string>

class SimpleWorkerResult : public WorkerResult
{
public:
    SimpleWorkerResult( const TaskResultCode resultCode ) :
        WorkerResult( resultCode )
    {}

    ComplexXmlElement toComplexXmlElement()
    {
        ComplexXmlElement resultsElement( "results" );

        resultsElement.appendSimpleElement( "resultcode", stringResultCode() );

        return resultsElement;
    }
};
