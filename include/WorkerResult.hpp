#ifndef _WORKERRESULT_HPP_
#define _WORKERRESULT_HPP_

#include <string>
#include <ComplexXmlElement.hpp>

struct WorkerResult
{
    bool success;
    virtual ComplexXmlElement toComplexXmlElement( ) = 0;
};

#endif // _WORKERRESULT_HPP_