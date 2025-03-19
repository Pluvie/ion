#include "json.h"

void test_suite__json (
    void
)
{
  test_add( json_decode, array );
  test_add( json_decode, array_empty );
  test_add( json_decode, array_maxlength );
  test_add( json_decode, array_minlength );
  test_add( json_decode, array_nested );
  test_add( json_decode, null_value );
  test_add( json_decode, primitive );
  test_add( json_decode, primitive_not_supported );
  test_add( json_decode, sequence );
  test_add( json_decode, sequence_overlength );
  test_add( json_decode, struct );
  test_add( json_decode, struct_empty );
  test_add( json_decode, vector );
  test_add( json_decode, vector_maxlength );
  test_add( json_decode, vector_minlength );
  test_add( json_encode, primitive );
  test_add( json_encode, struct );
  test_add( json_parse_number, error_eof );
  test_add( json_parse_number, error_exponent );
  test_add( json_parse_number, error_exponent_eof );
  test_add( json_parse_number, error_fractional );
  test_add( json_parse_number, error_fractional_eof );
  test_add( json_parse_number, error_hex );
  test_add( json_parse_number, error_number );
  test_add( json_parse_number, error_oct );
  test_add( json_parse_number, exponent );
  test_add( json_parse_number, exponent_negative );
  test_add( json_parse_number, integer );
  test_add( json_parse_number, integer_negative );
  test_add( json_parse_number, fractional );
  test_add( json_parse_number, fractional_negative );
  test_add( json_parse_string, correct );
  test_add( json_parse_string, escaped_double_quote );
  test_add( json_parse_string, escaped_other );
  test_add( json_parse_string, incorrect );
  test_add( json_parse_string, unterminated );
}
