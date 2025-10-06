#include "set_has.h"

spec( set_has ) {
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
      bool result = set_has(set, element);

      must("not fail");
        verify(failure.occurred == false);

      must("return true");
        verify(result == true);

      success();
    } end();

    when("the element is not present in the set") {
      element = "f";
      apply(stack_allocated_set_condition);
      bool result = set_has(set, element);

      must("not fail");
        verify(failure.occurred == false);

      must("return false");
        verify(result == false);

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
      bool result = set_has(set, element);

      must("not fail");
        verify(failure.occurred == false);

      must("return true");
        verify(result == true);

      success();
    } end();

    when("the element is not present in the set") {
      element = "f";
      apply(heap_allocated_set_condition);
      bool result = set_has(set, element);

      must("not fail");
        verify(failure.occurred == false);

      must("return false");
        verify(result == false);

      success();
    } end();
  } end();
  #undef heap_allocated_set_condition
}
