#include "set.h"

void test_suite__set (
    void
)
{
  test_add( set_add, increase_length );
  test_add( set_add, already_present );
  //test_add( set_each, avoid_empty );
  //test_add( set_get, string_keys );
  //test_add( set_get, value_at_key );
  //test_add( set_init, default_capacity );
  //test_add( set_init, immediate_allocation );
  //test_add( set_init, power_2_capacity );
  //test_add( set_rehash, data_invariance );
  //test_add( set_rehash, doubled_capacity );
  //test_add( set_set, complex_types );
  //test_add( set_set, rehash_trigger );
}
