#include "functions/bit_count_leading_ones.h"
#include "functions/bit_count_leading_zeros.h"
#include "functions/memory_acquire.h"
#include "functions/memory_acquire_aligned.h"
#include "functions/memory_copy.h"
#include "functions/memory_release.h"
#include "functions/memory_release_aligned.h"
#include "functions/memory_resize.h"
#include "functions/memory_set.h"
#include "functions/print_args.h"
#include "functions/print_failure.h"
#include "functions/print_hex.h"
#include "functions/print_variadic.h"

/*
struct allocator  allocator_init(int initial_capacity, int alignment);
void*             allocator_pop(struct allocator* space, int amount);
void*             allocator_push(struct allocator* space, int amount);
void              allocator_release(struct allocator* space);
void              allocator_reset(struct allocator* space);
*/
