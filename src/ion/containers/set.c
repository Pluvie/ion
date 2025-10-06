#define _type(...) __type(__VA_ARGS__)
#define __type(t, ...) t
#define T _type(set_of)

#include "set/functions.c"

#undef T
#undef _type
#undef __type

#undef set_of
