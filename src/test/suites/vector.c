#include "vector.h"

void test_suite__vector (
    void
)
{
  test_add( vector_get, element_at_position );
  test_add( vector_get, position_out_of_bounds );
  test_add( vector_init, correct_length );
}
