#define LINUX         1
#define WINDOWS_32    2
#define WINDOWS_64    3
#define WINDOWS       (WINDOWS_32 | WINDOWS_64)

#define platform(name) (PLATFORM & name) > 0

#if   platform(LINUX)
  #include "platform/linux.h"

#elif platform(WINDOWS_32)
  #include "platform/windows_32.h"

#elif platform(WINDOWS_64)
  #include "platform/windows_64.h"

#else
  #error "⚡️ION⚡️: Unsupported platform."
#endif
