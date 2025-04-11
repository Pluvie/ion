#include "map.h"

void test_suite__map (
    void
)
{
  test_add( map_each, avoid_empty );
  test_add( map_get, string_keys );
  test_add( map_get, value_at_key );
  test_add( map_init, default_capacity );
  test_add( map_init, immediate_allocation );
  test_add( map_init, power_2_capacity );
  test_add( map_rehash, data_invariance );
  test_add( map_rehash, doubled_capacity );
  test_add( map_set, complex_types );
  test_add( map_set, rehash_trigger );
}
