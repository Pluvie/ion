#include "core.h"

void test_suite__core (
    void
)
{
  test_add( buffer_alloc, address_unreliability );
  test_add( buffer_alloc, data_consistency );
  test_add( buffer_alloc, dynamic_grow_double_cap );
  test_add( buffer_alloc, dynamic_grow_next_pow_2 );
  test_add( buffer_alloc, first_alloc_aligned );
  test_add( buffer_alloc, increment_position );
  test_add( buffer_init, default_capacity );
  test_add( buffer_init, no_immediate_allocation );
  test_add( buffer_init, power_2_capacity );
  test_add( memory_alloc, dynamic_grow_double_cap );
  test_add( memory_alloc, dynamic_grow_next_pow_2 );
  test_add( memory_alloc, first_alloc_aligned );
  test_add( memory_alloc, increment_position );
  test_add( memory_alloc_zero, zero_out );
  test_add( memory_init, default_capacity );
  test_add( memory_init, no_immediate_allocation );
  test_add( memory_init, power_2_capacity );
  test_add( signal_catch, intercept );
}
