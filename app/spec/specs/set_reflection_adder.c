#include "set_reflection_adder.h"

spec( set_reflection_adder ) {
  argument(void* set);
  argument(void* element);

  precondition("a valid set");
    set<int> valid_set = set_alloc(int, 8, spec_allocator);
    set_add(&valid_set, 3);
    set_add(&valid_set, 4);
    set = &valid_set;

  precondition("a valid element")
    int _element = 5; element = &_element;

  must("behave exactly like set_add");
    set<int> other_set = set_alloc(int, 8, spec_allocator);
    set_add(&other_set, 3);
    set_add(&other_set, 4);

    unsigned int result = set<int>_reflection_adder(set, element);
    unsigned int other_set_result = set_add(&other_set, *(int*) element);

    verify(result == other_set_result);
    verify(valid_set.length == other_set.length);
    verify(valid_set.capacity == other_set.capacity);
    verify(valid_set.allocator == other_set.allocator);

  success();
}
