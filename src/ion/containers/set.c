#define T container_for
#define N container_name
#define concat_function(name, func) name ## _ ## func
#define container_function(name, func) concat_function(name, func)

#include "set/macros.h"
#include "set/functions.c"
#include "set/macros.h"

#undef T
#undef N
#undef container_for
#undef container_name
#undef container_hasher
#undef container_equalizer
#undef container_function
#undef concat_function
