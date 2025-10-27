#define T container_for
#define N container_name
#define concat_function(name, func) name ## _ ## func
#define container_function(name, func) concat_function(name, func)

#include "set/struct.h"
#include "set/functions.h"

#undef T
#undef N
#undef container_for
#undef container_name
#undef container_function
#undef concat_function
