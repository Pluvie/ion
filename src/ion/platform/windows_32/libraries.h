#include <stdarg.h>
#if standard(>= C23)
#include <stdbit.h>
#endif
#if standard(<= C17)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#if standard(>= C11)
#include <malloc.h>
#define aligned_alloc _aligned_alloc
#define aligned_free  _aligned_free
#endif
