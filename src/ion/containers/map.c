#define _key_type(...) __key_type(__VA_ARGS__)
#define _value_type(...) __value_type(__VA_ARGS__)
#define __key_type(kt, vt, ...) kt
#define __value_type(kt, vt, ...) vt
#define K _key_type(map_of)
#define V _value_type(map_of)

#ifdef  map_cmp_function
#define set_cmp_function map_cmp_function
#endif
#ifdef  map_hash_function
#define set_hash_function map_hash_function
#endif

#include "map/functions.c"

#undef K
#undef V
#undef _key_type
#undef __key_type
#undef _value_type
#undef __value_type

#undef map_of
#undef map_cmp_function
#undef map_hash_function
#undef set_cmp_function
#undef set_hash_function
