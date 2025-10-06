#include "set_del.h"

spec( set_del ) {
  argument(set<char*>* set);
  argument(char* element);

  when("the set is stack allocated") {
    #define stack_allocated_set_condition \
      set<char*> stack_set = set_init(char*, 16); \
      set = &stack_set; \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c");

    when("the element is present in the set") {
      element = "a";
      apply(stack_allocated_set_condition);
      int original_set_length = set->length;
      int original_set_capacity = set->capacity;
      int result = set_del(set, element);

      must("decrease the set length by 1");
        verify(set->length == original_set_length - 1);

      must("return the position of the deleted element");
        verify(result != (unsigned int) -1);

      must("leave the set capacity unchanged");
        verify(set->capacity == original_set_capacity);

      success();
    } end();

    when("the element is not present in the set") {
      element = "f";
      apply(stack_allocated_set_condition);
      int original_set_length = set->length;
      int original_set_capacity = set->capacity;
      int result = set_del(set, element);

      must("leave the set length unchanged");
        verify(set->length == original_set_length);

      must("return -1");
        verify(result == (unsigned int) -1);

      must("leave the set capacity unchanged");
        verify(set->capacity == original_set_capacity);

      success();
    } end();
  } end();
  #undef stack_allocated_set_condition

  when("the set is heap allocated") {
    #define heap_allocated_set_condition \
      set = allocator_push(spec_allocator, sizeof(*set)); \
      *set = set_alloc(char*, 16, spec_allocator); \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c");

    when("the element is present in the set") {
      element = "a";
      apply(heap_allocated_set_condition);
      int original_set_length = set->length;
      int original_set_capacity = set->capacity;
      int result = set_del(set, element);

      must("decrease the set length by 1");
        verify(set->length == original_set_length - 1);

      must("return the position of the deleted element");
        verify(result != (unsigned int) -1);

      must("leave the set capacity unchanged");
        verify(set->capacity == original_set_capacity);

      success();
    } end();

    when("the element is not present in the set") {
      element = "f";
      apply(heap_allocated_set_condition);
      int original_set_length = set->length;
      int original_set_capacity = set->capacity;
      int result = set_del(set, element);

      must("leave the set length unchanged");
        verify(set->length == original_set_length);

      must("return -1");
        verify(result == (unsigned int) -1);

      must("leave the set capacity unchanged");
        verify(set->capacity == original_set_capacity);

      success();
    } end();
  } end();
  #undef heap_allocated_set_condition
}
