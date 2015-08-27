#ifndef _TASKTYPEMAP_HPP_
#define _TASKTYPEMAP_HPP_

#include "ConstMap.hpp"
#include "TaskTypeEnum.h"

#include <string>

class TaskTypeMap : public ConstMap<std::string, TaskType>
{
private:

    void init();

public:
    TaskTypeMap() { init(); }
    ~TaskTypeMap() {}
};

#endif
