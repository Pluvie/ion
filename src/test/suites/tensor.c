#include "tensor.h"

void test_suite__tensor (
    void
)
{
  test_add( tensor_at, correct_offsets );
  test_add( tensor_init, correct_dimensions );
  test_add( tensor_init, correct_length );
  test_add( tensor_init, correct_offsets );
}
