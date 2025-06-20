#include "test.h"
#include "ion.c"

int32 main (
    int32 argc,
    char** argv
)
{
  test_add( date, day_month_year );
  test_add( date_to_string, format );
  test_add( date_today, correct_number );
  test_add( failure, fail_macro );
  test_add( io, io_macro );
  test_add( io_buffer_read, available_space );
  test_add( io_buffer_read, chip_away );
  test_add( io_buffer_read, extend );
  test_add( io_open, autocalc_length );
  test_add( io_read_descriptor, cursor_advance );
  test_add( io_read_descriptor, cursor_advance_partial );
  test_add( io_read_descriptor, read_error );
  test_add( list, user_defined_types );
  test_add( list_alloc, enforce_capacity );
  test_add( list_alloc, enforce_capacity_pow2 );
  test_add( list_alloc, heap_allocated );
  test_add( list_at, over_bounds );
  test_add( list_at, under_bounds );
  test_add( list_at, valid );
  test_add( list_each, iterate_elements );
  test_add( list_init, stack_allocated );
  test_add( list_literal, frozen );
  test_add( list_pop, decrease_length );
  test_add( list_pop, zero_length );
  test_add( list_push, copy_element );
  test_add( list_push, grow_trigger );
  test_add( list_push, increase_length );
  test_add( map, user_defined_types );
  test_add( map_del, decrease_length );
  test_add( map_del, invariance_on_missing );
  test_add( map_each, iterate_keys_and_values );
  test_add( map_has, deleted );
  test_add( map_has, not_present );
  test_add( map_has, present );
  test_add( map_literal, frozen );
  test_add( map_set, increase_length );
  test_add( map_set, rehash_trigger );
  test_add( memory_alloc, first_allocation );
  test_add( memory_alloc, first_allocation_capacity );
  test_add( memory_alloc, first_allocation_capacity_surpassed );
  test_add( memory_alloc, next_allocation_fitting );
  test_add( memory_alloc, next_allocation_unfitting );
  test_add( memory_alloc, regions_saturation );
  test_add( memory_init, initialize_empty );
  test_add( memory_init, negative_capacity );
  test_add( reflection_macros, array_type );
  test_add( reflection_macros, array_type_referenced );
  test_add( reflection_macros, array_type_tagless );
  test_add( reflection_macros, list_type );
  test_add( reflection_macros, list_type_limited );
  test_add( reflection_macros, list_type_nested );
  test_add( reflection_macros, struct_type );
  test_add( reflection_macros, struct_type_define );
  test_add( reflection_macros, struct_type_tagless );
  test_add( set, user_defined_types );
  test_add( set_add, increase_length );
  test_add( set_add, occupy_pos );
  test_add( set_add, rehash_trigger );
  test_add( set_alloc, enforce_capacity );
  test_add( set_alloc, enforce_capacity_pow2 );
  test_add( set_alloc, heap_allocated );
  test_add( set_del, decrease_length );
  test_add( set_del, invariance_on_missing );
  test_add( set_each, iterate_elements );
  test_add( set_has, deleted );
  test_add( set_has, not_present );
  test_add( set_has, present );
  test_add( set_init, stack_allocated );
  test_add( set_literal, frozen );
  test_add( set_pos, free );
  test_add( set_pos, not_present );
  test_add( set_pos, present );
  test_add( set_rehash, data_invariance );
  test_add( set_rehash, doubled_capacity );
  test_add( string_literal, s_macro );
  test_add( string_to_dec, contained );
  test_add( string_to_int, contained );
  test_add( string_to_int, overflow );
  test_add( string_to_int, underflow );
  test_add( time_now, correct_number );
  test_add( time_to_string, format );

  tests_run();

  if (tests_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
