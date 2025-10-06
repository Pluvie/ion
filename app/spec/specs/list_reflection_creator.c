#include "list_reflection_creator.h"

spec( list_reflection_creator ) {
  argument(void* address);
  argument(unsigned int capacity);
  argument(struct allocator* allocator);

  precondition("a valid address of a list");
    list<int> list = { 0 }; address = &list;

  precondition("a valid capacity")
    capacity = 11;

  precondition("a valid allocator")
    allocator = spec_allocator;

  must("behave exactly like list_alloc");
    list<int> other_list = list_alloc(int, capacity, allocator);
    list<int>_reflection_creator(address, capacity, allocator);

    verify(list.data != nullptr);
    verify(list.length == other_list.length);
    verify(list.capacity == other_list.capacity);
    verify(list.allocator == other_list.allocator);

  success();
}
