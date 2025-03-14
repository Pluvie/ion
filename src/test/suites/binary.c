#include "binary.h"

void test_suite__binary (
    void
)
{
  test_add( binary_decode, array );
  test_add( binary_decode, array_maxlength );
  test_add( binary_decode, array_minlength );
  test_add( binary_decode, pointer );
  test_add( binary_decode, primitive );
  test_add( binary_decode, sequence );
  test_add( binary_decode, string );
  test_add( binary_decode, validator );
  test_add( binary_decode, vector );
  test_add( binary_decode, vector_maxlength );
  test_add( binary_decode, vector_minlength );
  test_add( binary_encode, array );
  test_add( binary_encode, pointer );
  test_add( binary_encode, primitive );
  test_add( binary_encode, sequence );
  test_add( binary_encode, string );
  test_add( binary_encode, vector );
  test_add( binary_protocol, round_trip );
}
