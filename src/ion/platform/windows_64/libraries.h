#include <stdarg.h>
#if standard(>= C23)
#include <stdbit.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <malloc.h>
#define aligned_alloc _aligned_alloc
#define aligned_free  _aligned_free
