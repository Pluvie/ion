#include "string.h"

void test_suite__string (
    void
)
{
  test_add( string_to_number, decimal_128 );
  test_add( string_to_number, decimal_32 );
  test_add( string_to_number, decimal_64 );
  test_add( string_to_number, integer_consistency_exponent );
  test_add( string_to_number, integer_consistency_fractional );
  test_add( string_to_number, signed_16 );
  test_add( string_to_number, signed_16_overflow );
  test_add( string_to_number, signed_16_underflow );
  test_add( string_to_number, signed_32 );
  test_add( string_to_number, signed_32_overflow );
  test_add( string_to_number, signed_32_underflow );
  test_add( string_to_number, signed_64 );
  test_add( string_to_number, signed_64_overflow );
  test_add( string_to_number, signed_64_underflow );
  test_add( string_to_number, signed_8 );
  test_add( string_to_number, signed_8_overflow );
  test_add( string_to_number, signed_8_underflow );
  test_add( string_to_number, type_not_numeric );
  test_add( string_to_number, unsigned_16 );
  test_add( string_to_number, unsigned_16_overflow );
  test_add( string_to_number, unsigned_32 );
  test_add( string_to_number, unsigned_32_overflow );
  test_add( string_to_number, unsigned_64 );
  test_add( string_to_number, unsigned_64_overflow );
  test_add( string_to_number, unsigned_8 );
  test_add( string_to_number, unsigned_8_overflow );
  test_add( string_to_number, unsigned_consistency );
  test_add( string_split, array_of_chunks );
  test_add( string_split, wrapped );
  test_add( string_split, wrapped_incomplete );
  test_add( string_split, wrapped_unterminated );
  test_add( string_split, zero_length );
}
