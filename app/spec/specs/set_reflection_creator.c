#include "set_reflection_creator.h"

spec( set_reflection_creator ) {
  argument(void* address);
  argument(unsigned int capacity);
  argument(struct allocator* allocator);

  precondition("a valid address of a set");
    set<int> set = { 0 }; address = &set;

  precondition("a valid capacity")
    capacity = 11;

  precondition("a valid allocator")
    allocator = spec_allocator;

  must("behave exactly like set_alloc");
    set<int> other_set = set_alloc(int, capacity, allocator);
    set<int>_reflection_creator(address, capacity, allocator);

    verify(set.data != nullptr);
    verify(set.length == other_set.length);
    verify(set.capacity == other_set.capacity);
    verify(set.allocator == other_set.allocator);

  success();
}
