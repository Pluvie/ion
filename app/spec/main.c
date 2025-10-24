#include "spec.h"
#include "spec.c"

#include <ion.c>

spec( allocator_init );
spec( allocator_pop );
spec( allocator_push );
spec( allocator_release );
spec( allocator_reset );
spec( bit_count_leading_ones );
spec( bit_count_leading_zeros );
spec( cstr_compare );
spec( cstr_equal );
spec( hash_djb2 );
spec( hash_djb2_cstr );
spec( fail );
spec( fatal );
spec( list );
spec( list_alloc );
spec( list_at );
spec( list_del );
spec( list_each );
spec( list_init );
spec( list_init );
spec( list_pop );
spec( list_push );
spec( list_reflection_adder );
spec( list_reflection_creator );
spec( list_sort );
spec( map );
spec( map_alloc );
spec( map_del );
spec( map_each );
spec( map_get );
spec( map_has );
spec( map_init );
spec( map_reflection_adder );
spec( map_reflection_creator );
spec( map_set );
spec( memory_acquire );
spec( memory_acquire_aligned );
spec( memory_copy );
spec( memory_release );
spec( memory_release_aligned );
spec( memory_resize );
spec( memory_set );
spec( print );
spec( printl );
spec( prints );
spec( reflection );
spec( reflection_field_find );
spec( reflection_validate );
spec( set );
spec( set_add );
spec( set_alloc );
spec( set_del );
spec( set_each );
spec( set_init );
spec( set_pos );
spec( set_reflection_adder );
spec( set_reflection_creator );
spec( str_build );
spec( str_compare );
spec( str_empty );
spec( str_equal );
spec( str_to_dec );
spec( str_to_int );
#if standard(>= C11)
spec( thread_pool_create );
spec( thread_pool_enqueue );
spec( thread_pool_wait );
#endif

int0 main (
    int0 argc,
    char** argv
)
{
  spec_add( allocator_init );
  spec_add( allocator_pop );
  spec_add( allocator_push );
  spec_add( allocator_release );
  spec_add( allocator_reset );
  spec_add( bit_count_leading_ones );
  spec_add( bit_count_leading_zeros );
  spec_add( cstr_compare );
  spec_add( cstr_equal );
  spec_add( hash_djb2 );
  spec_add( hash_djb2_cstr );
  spec_add( fail );
  spec_add( fatal );
  spec_add( list );
  spec_add( list_alloc );
  spec_add( list_at );
  spec_add( list_del );
  spec_add( list_each );
  spec_add( list_init );
  spec_add( list_init );
  spec_add( list_pop );
  spec_add( list_push );
  spec_add( list_reflection_adder );
  spec_add( list_reflection_creator );
  spec_add( list_sort );
  spec_add( map );
  spec_add( map_alloc );
  spec_add( map_del );
  spec_add( map_each );
  spec_add( map_get );
  spec_add( map_has );
  spec_add( map_init );
  spec_add( map_reflection_adder );
  spec_add( map_reflection_creator );
  spec_add( map_set );
  spec_add( memory_acquire );
  spec_add( memory_acquire_aligned );
  spec_add( memory_copy );
  spec_add( memory_release );
  spec_add( memory_release_aligned );
  spec_add( memory_resize );
  spec_add( memory_set );
  spec_add( print );
  spec_add( printl );
  spec_add( prints );
  spec_add( reflection );
  spec_add( reflection_field_find );
  spec_add( reflection_validate );
  spec_add( set );
  spec_add( set_add );
  spec_add( set_alloc );
  spec_add( set_del );
  spec_add( set_each );
  spec_add( set_init );
  spec_add( set_pos );
  spec_add( set_reflection_adder );
  spec_add( set_reflection_creator );
  spec_add( str_build );
  spec_add( str_compare );
  spec_add( str_empty );
  spec_add( str_equal );
  spec_add( str_to_dec );
  spec_add( str_to_int );
  #if standard(>= C11)
  spec_add( thread_pool_create );
  spec_add( thread_pool_enqueue );
  spec_add( thread_pool_wait );
  #endif

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
