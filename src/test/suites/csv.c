#include "csv.h"

void test_suite__csv (
    void
)
{
  test_add( csv_is_reflection_compatible, compatible );
  test_add( csv_is_reflection_compatible, incompatible_struct_fields );
  test_add( csv_is_reflection_compatible, not_array );
  test_add( csv_is_reflection_compatible, not_array_of_struct );
  test_add( csv_string_split, array_of_chunks );
  test_add( csv_string_split, wrapped );
  test_add( csv_string_split, wrapped_incomplete );
  test_add( csv_string_split, wrapped_unterminated );
  test_add( csv_string_split, zero_length );
}
