#include <ion.h>
#include <ion/spec.h>

#include <ion.c>
#include <ion/spec.c>

spec( allocator_init );
spec( allocator_pop );
spec( allocator_push );
spec( allocator_release );
spec( bit_count_leading_ones );
spec( bit_count_leading_zeros );
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
spec( str_empty );
spec( str_equal );
spec( str_to_dec );
spec( str_to_int );

int_t main (
    int_t argc,
    cstr* argv
)
{
  spec_add( allocator_init );
  spec_add( allocator_pop );
  spec_add( allocator_push );
  spec_add( allocator_release );
  spec_add( bit_count_leading_ones );
  spec_add( bit_count_leading_zeros );
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
  spec_add( str_compare );
  spec_add( str_empty );
  spec_add( str_equal );
  spec_add( str_to_dec );
  spec_add( str_to_int );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
