#define _type(...) __type(__VA_ARGS__)
#define __type(t, ...) t
#define T _type(list_of)

#include "list/functions.c"

#undef T
#undef _type
#undef __type

#undef list_of
#undef list_cmp_function
