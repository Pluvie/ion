#include "../simulation/abort.h"

#include "../../ion/modules/core.c"

#include "core/buffer_alloc/address_unreliability.c"
#include "core/buffer_alloc/data_consistency.c"
#include "core/buffer_alloc/dynamic_grow_double_cap.c"
#include "core/buffer_alloc/dynamic_grow_next_pow_2.c"
#include "core/buffer_alloc/first_alloc_aligned.c"
#include "core/buffer_alloc/increment_position.c"
#include "core/buffer_init/default_capacity.c"
#include "core/buffer_init/no_immediate_allocation.c"
#include "core/buffer_init/power_2_capacity.c"
#include "core/memory_alloc/dynamic_grow_double_cap.c"
#include "core/memory_alloc/dynamic_grow_next_pow_2.c"
#include "core/memory_alloc/first_alloc_aligned.c"
#include "core/memory_alloc/increment_position.c"
#include "core/memory_alloc_zero/zero_out.c"
#include "core/memory_init/default_capacity.c"
#include "core/memory_init/no_immediate_allocation.c"
#include "core/memory_init/power_2_capacity.c"
#include "core/signal_catch/intercept.c"
