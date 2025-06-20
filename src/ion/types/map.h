#define _key_type(...) __key_type(__VA_ARGS__)
#define _value_type(...) __value_type(__VA_ARGS__)
#define __key_type(kt, vt, ...) kt
#define __value_type(kt, vt, ...) vt
#define K _key_type(map_of)
#define V _value_type(map_of)

#include "map/struct.h"
#include "map/functions.h"

#undef K
#undef V
#undef _key_type
#undef __key_type
#undef _value_type
#undef __value_type

#undef map_of
