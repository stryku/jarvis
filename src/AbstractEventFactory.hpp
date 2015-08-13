#pragma once

#include "AbstractEvent.hpp"
#include "InputEventType.h"

#include <memory>

class AbstractEventFactory
{
protected:
    typedef std::shared_ptr<AbstractEvent> EventPtr;

public:
    virtual EventPtr getEvent( InputEventType type, const std::string &xmlData ) = 0;
};
