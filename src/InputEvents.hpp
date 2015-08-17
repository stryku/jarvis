#pragma once

#ifdef WIN32
#include "windows/InputEvents.hpp"
#endif // WIN32

#ifdef __linux__
#include "linux/InputEvents.hpp"
#endif
