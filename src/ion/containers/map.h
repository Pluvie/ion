#define concat_function(name, func) name ## _ ## func
#define container_function(name, func) concat_function(name, func)

/* Autodefines the keys set type. */
#define N container_function(container_name, keys)
#define T container_for_key
#include "set/struct.h"
#include "set/functions.h"
#undef  N
#undef  T

#define K container_for_key
#define V container_for_value
#define N container_name
#define S container_function(container_name, keys)
#include "map/struct.h"
#include "map/functions.h"

#undef K
#undef V
#undef N
#undef S
#undef container_for_key
#undef container_for_value
#undef container_name
#undef container_function
#undef concat_function
