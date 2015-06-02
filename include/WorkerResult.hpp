#ifndef _WORKERRESULT_HPP_
#define _WORKERRESULT_HPP_

#include <string>
#include <ComplexDataElement.hpp>

struct WorkerResult
{
    virtual ComplexDataElement toComplexDataElement( ) = 0;
};

#endif // _WORKERRESULT_HPP_