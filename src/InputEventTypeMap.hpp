#pragma once

#include "ConstMap.hpp"
#include "InputEventType.h"

#include <string>

class InputEventTypeMap : public ConstMap<std::string, InputEventType>
{
private:
    void init();

public:
    InputEventTypeMap() { init(); }
    ~InputEventTypeMap() {}
};
