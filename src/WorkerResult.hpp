#ifndef _WORKERRC_HPP_
#define _WORKERRC_HPP_

#include "ComplexXmlElement.hpp"
#include "TaskResultCode.h"

#include <string>

class WorkerResult
{
protected:
    TaskResultCode resultCode;
    
    std::string stringResultCode( ) const
    {
        switch( resultCode )
        {
            case RC_SUCCESS: return "RC_SUCCESS";
            case RC_FAIL: return "RC_FAIL";

            default: return "RC_UNDEF";
        }
    }

public:
    WorkerResult( TaskResultCode rc ) :
        resultCode(rc)
    {}
    virtual ~WorkerResult() {}

    virtual ComplexXmlElement toComplexXmlElement() = 0;
};

#endif // _WORKERRC_HPP_
