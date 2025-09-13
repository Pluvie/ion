#include "functions/bit_count_leading_ones.h"
#include "functions/bit_count_leading_zeros.h"
#include "functions/fail.h"
#include "functions/fatal.h"
#include "functions/print.h"

#include "functions/memory_release.h"
#include "functions/memory_require.h"
#include "functions/memory_resize.h"

/*
struct allocator  allocator_init(int initial_capacity, int alignment);
void*             allocator_pop(struct allocator* space, int amount);
void*             allocator_push(struct allocator* space, int amount);
void              allocator_release(struct allocator* space);
void              allocator_reset(struct allocator* space);
*/
