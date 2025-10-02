#define _type(...) __type(__VA_ARGS__)
#define __type(t, ...) t
#define T _type(list_of)

#include "list/struct.h"
#include "list/functions.h"
#include "list/reflection.h"

#undef T
#undef _type
#undef __type

#undef list_of
