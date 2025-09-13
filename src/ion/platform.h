#define platform(name) PLATFORM == name

#if   platform(LINUX)
  #include "platform/linux.h"

#elif platform(WINDOWS_32)
  #include "platform/windows_32.h"

#elif platform(WINDOWS_64)
  #include "platform/windows_64.h"

#else
  #error "⚡️ION⚡️: Unsupported platform."
#endif
