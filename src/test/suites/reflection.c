#include "reflection.h"

void test_suite__reflection (
    void
)
{
  test_add( error_add_reflection_path, preserve_trace );
  test_add( reflection_path_print, dot_separated );
  test_add( reflection_path_print, empty );
  test_add( reflection_path_print, index );
  test_add( reflection_inspect, print_object );
  test_add( reflection_macros, array_type );
  test_add( reflection_macros, array_type_limited );
  test_add( reflection_macros, array_type_nested );
  test_add( reflection_macros, sequence_type );
  test_add( reflection_macros, sequence_type_referenced );
  test_add( reflection_macros, sequence_type_tagless );
  test_add( reflection_macros, struct_type );
  test_add( reflection_macros, struct_type_defined );
  test_add( reflection_macros, struct_type_tagless );
  test_add( reflection_macros, vector_type );
}
