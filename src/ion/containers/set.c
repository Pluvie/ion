#define T container_for
#define N container_name
#define concat_function(name, func) name ## _ ## func
#define container_function(name, func) concat_function(name, func)

#define memory_set memset
#include "set/macros.h"
#include "set/functions.c"
#include "set/macros.h"
#undef memory_set

#undef T
#undef N
#undef container_for
#undef container_name
#undef container_function
#undef concat_function

#undef set_of
