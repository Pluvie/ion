#include "array.h"

void test_suite__array (
    void
)
{
  test_add( array_each, iterate_elements );
  test_add( array_get, element_at_position );
  test_add( array_get, position_out_of_bounds );
  test_add( array_init, default_capacity );
  test_add( array_init, immediate_allocation );
  test_add( array_init, power_2_capacity );
  test_add( array_pop, decrease_length );
  test_add( array_pop, preserve_capacity );
  test_add( array_push, complex_types );
  test_add( array_push, increase_length );
  test_add( array_push, increase_capacity );
  test_add( array_push, stack_allocated );
  test_add( array_set, element_at_position );
  test_add( array_set, position_out_of_bounds );
}
