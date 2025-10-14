#include "map_reflection_creator.h"

spec( map_reflection_creator ) {
  argument(void* address);
  argument(unsigned int capacity);
  argument(struct allocator* allocator);

  precondition("a valid address of a map");
    map<char*, int> map = { 0 }; address = &map;

  precondition("a valid capacity")
    capacity = 11;

  precondition("a valid allocator")
    allocator = spec_allocator;

  must("behave exactly like map_alloc");
    map<char*, int> other_map = map_alloc(char*, int, capacity, allocator);
    map<char*, int>_reflection_creator(address, capacity, allocator);

    verify(map.values != nullptr);
    verify(map.length == other_map.length);
    verify(map.keys.capacity == other_map.keys.capacity);
    verify(map.keys.allocator == other_map.keys.allocator);

  success();
}
