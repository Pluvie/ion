#ifndef ION_CORE
#error ⚡️ION⚡️ CORE module is required. Include <ion/modules/core.h>.
#endif

#ifndef ION_IO
#error ⚡️ION⚡️ IO module is required. Include <ion/modules/io.h>.
#endif

#define ION_TCP

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#include "tcp/structs.h"
#include "tcp/functions.h"
