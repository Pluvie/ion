/* ⚡️ION⚡️ platforms mapping. */

#ifndef PLATFORM
#error "ION: Specify a target platform."
#endif

#define LINUX     0
#define WINDOWS   1

#define platform(name) (PLATFORM == name)

#if   platform(LINUX)
#include "platform/linux.h"

#elif platform(WINDOWS)
#include "platform/windows.h"

#else
#error "ION: Unsupported platform -- contributions to support it are most welcome."
#endif
