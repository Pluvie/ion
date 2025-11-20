#include <ion.h>
#include <ion/spec.h>

#include <ion.c>
#include <ion/spec.c>

spec( arena_create );
spec( arena_destroy );
spec( arena_push );
spec( bit_count_leading_ones );
spec( bit_count_leading_zeros );
spec( buffer_create );
spec( buffer_destroy );
spec( buffer_pointer );
spec( buffer_pointer_at );
spec( buffer_position_get );
spec( buffer_position_set );
spec( buffer_push );
spec( cstr_compare );
spec( cstr_equal );
spec( map_alloc );
spec( map_del );
spec( map_each );
spec( map_get );
spec( map_has );
spec( map_literal );
spec( map_set );
spec( memory_acquire );
spec( memory_acquire_aligned );
spec( memory_compare );
spec( memory_copy );
spec( memory_equal );
spec( memory_release );
spec( memory_release_aligned );
spec( memory_set );
spec( str_compare );
spec( str_compare_case );
spec( str_append );
spec( str_empty );
spec( str_equal );
spec( str_equal_case );
spec( str_strip );
spec( str_to_dec );
spec( str_to_int );

int_t main (
    int_t argc,
    cstr* argv
)
{
  spec_add( arena_create );
  spec_add( arena_destroy );
  spec_add( arena_push );
  spec_add( bit_count_leading_ones );
  spec_add( bit_count_leading_zeros );
  spec_add( buffer_create );
  spec_add( buffer_destroy );
  spec_add( buffer_pointer );
  spec_add( buffer_pointer_at );
  spec_add( buffer_position_get );
  spec_add( buffer_position_set );
  spec_add( cstr_compare );
  spec_add( cstr_equal );
  spec_add( map_alloc );
  spec_add( map_del );
  spec_add( map_each );
  spec_add( map_get );
  spec_add( map_has );
  spec_add( map_literal );
  spec_add( map_set );
  spec_add( memory_acquire );
  spec_add( memory_acquire_aligned );
  spec_add( memory_compare );
  spec_add( memory_copy );
  spec_add( memory_equal );
  spec_add( memory_release );
  spec_add( memory_release_aligned );
  spec_add( memory_set );
  spec_add( str_append );
  spec_add( str_compare );
  spec_add( str_compare_case );
  spec_add( str_empty );
  spec_add( str_equal );
  spec_add( str_equal_case );
  spec_add( str_strip );
  spec_add( str_to_dec );
  spec_add( str_to_int );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
