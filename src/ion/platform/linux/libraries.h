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
#define aligned_free  free
#endif
