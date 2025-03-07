#include "csv.h"

void test_suite__csv (
    void
)
{
  test_add( csv_decode_headers, matching_fields );
  test_add( csv_decode_headers, unmatching_fields );
  test_add( csv_decode_row, field_types );
  test_add( csv_is_reflection_compatible, compatible );
  test_add( csv_is_reflection_compatible, incompatible_struct_fields );
  test_add( csv_is_reflection_compatible, not_array );
  test_add( csv_is_reflection_compatible, not_array_of_struct );
  test_add( csv_parse_row, comma_separated );
  test_add( csv_parse_row, comma_separated_wrapped );
  test_add( csv_parse_row, comma_separated_overcount );
  test_add( csv_parse_row, malformed_wrapper );
  test_add( csv_parse_row, multiple_rows );
  test_add( csv_parse_row, multiple_rows_mixed );
  test_add( csv_parse_row, newline_unwrapped );
  test_add( csv_parse_row, newline_unwrapped_overcount );
  test_add( csv_parse_row, semicolon_separated );
  test_add( csv_parse_row, semicolon_separated_wrapped );
  test_add( csv_string_split, array_of_chunks );
  test_add( csv_string_split, wrapped );
  test_add( csv_string_split, wrapped_incomplete );
  test_add( csv_string_split, wrapped_unterminated );
  test_add( csv_string_split, zero_length );
}
