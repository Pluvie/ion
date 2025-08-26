#if platform(LINUX)
  #include "linux/structs.h"
#else
  #error "Unsupported platform."
#endif
