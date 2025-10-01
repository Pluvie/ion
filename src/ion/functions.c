#include "functions/allocator_init.c"
#include "functions/allocator_push.c"
#include "functions/allocator_release.c"
#include "functions/bit_count_leading_ones.c"
#include "functions/bit_count_leading_zeros.c"
#include "functions/memory_acquire.c"
#include "functions/memory_acquire_aligned.c"
#include "functions/memory_compare.c"
#include "functions/memory_copy.c"
#include "functions/memory_equal.c"
#include "functions/memory_release.c"
#include "functions/memory_release_aligned.c"
#include "functions/memory_resize.c"
#include "functions/memory_set.c"
#include "functions/print_args.c"
#include "functions/print_failure.c"
#include "functions/print_hex.c"
#include "functions/print_variadic.c"

/*
struct allocator  allocator_init(int initial_capacity, int alignment);
void*             allocator_pop(struct allocator* space, int amount);
void*             allocator_push(struct allocator* space, int amount);
void              allocator_release(struct allocator* space);
void              allocator_reset(struct allocator* space);
*/
