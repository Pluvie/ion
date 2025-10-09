#include "set_reflection_adder.h"

spec( set_reflection_adder ) {
  argument(void* generic_set);
  argument(void* generic_element);

  precondition("a valid set");
    set<int> set = set_alloc(int, 8, spec_allocator);
    set_add(&set, 3);
    set_add(&set, 4);
    generic_set = &set;

  precondition("a valid element")
    int element = 5; generic_element = &element;

  must("behave exactly like set_add");
    set<int> set_with_add = set_alloc(int, 8, spec_allocator);
    set_add(&set_with_add, 3);
    set_add(&set_with_add, 4);

    void* result = set<int>_reflection_adder(generic_set, generic_element);
    unsigned int set_result = (int*) result - set.data;
    unsigned int set_with_add_result = set_add(&set_with_add, element);

    verify(set_result == set_with_add_result);
    verify(set.length == set_with_add.length);
    verify(set.capacity == set_with_add.capacity);
    verify(set.allocator == set_with_add.allocator);

  success();
}
