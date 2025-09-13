#include "functions/bit_count_leading_ones.c"
#include "functions/bit_count_leading_zeros.c"
#include "functions/fail.c"
#include "functions/fatal.c"
#include "functions/print_formatted.c"

#include "functions/memory_release.c"
#include "functions/memory_require.c"
#include "functions/memory_resize.c"

/*
struct allocator  allocator_init(int initial_capacity, int alignment);
void*             allocator_pop(struct allocator* space, int amount);
void*             allocator_push(struct allocator* space, int amount);
void              allocator_release(struct allocator* space);
void              allocator_reset(struct allocator* space);
*/
