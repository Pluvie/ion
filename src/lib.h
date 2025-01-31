#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <immintrin.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <ion/typedefs.h>
#include <ion/constants.h>
#include <ion/enums.h>
#include <ion/macros.h>
#include <ion/structs.h>
#include <ion/globals.h>

/* Does not include all functions headers, as seen in the file `ion.h`, but only the
 * ones with a public API, which shall be exposed as library. The other functions
 * shall be inlined. */
#include <ion/functions/array_get.h>
#include <ion/functions/array_init.h>
#include <ion/functions/array_last.h>
#include <ion/functions/array_pop.h>
#include <ion/functions/array_print.h>
#include <ion/functions/array_push.h>
#include <ion/functions/array_set.h>
#include <ion/functions/binary_decode.h>
#include <ion/functions/date.h>
#include <ion/functions/date_to_string.h>
#include <ion/functions/hexdump.h>
#include <ion/functions/io_peek.h>
#include <ion/functions/io_read.h>
#include <ion/functions/io_write.h>
#include <ion/functions/map_get.h>
#include <ion/functions/map_init.h>
#include <ion/functions/map_print.h>
#include <ion/functions/map_set.h>
#include <ion/functions/memory_alloc.h>
#include <ion/functions/memory_alloc_zero.h>
#include <ion/functions/memory_init.h>
#include <ion/functions/memory_release.h>
#include <ion/functions/sci_notation_convert.h>
#include <ion/functions/time_now.h>
#include <ion/functions/time_to_string.h>
