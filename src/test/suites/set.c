#include "set.h"

void test_suite__set (
    void
)
{
  test_add( set_add, already_present );
  test_add( set_add, increase_length );
  test_add( set_del, not_present );
  test_add( set_del, present );
  test_add( set_has, not_present );
  test_add( set_has, present );
}
