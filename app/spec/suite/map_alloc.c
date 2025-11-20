#include "map_alloc.h"

spec( map_alloc ) {
  argument(int capacity);
  argument(struct arena* allocator);
  returns(struct cstr_int_map map);

  precondition("a valid allocator")
    allocator = spec_allocator;

  when("the capacity is less than 16") {
    capacity = 12;
    map = cstr_int_map_alloc(capacity, allocator);

    must("create an empty heap allocated map");
      verify(map.length == 0);
      verify(map.keys.allocator == spec_allocator);

    must("enforce the map capacity to 16");
      verify(map.keys.capacity == 16);

    success();
  } end();

  when("the capacity is greater than 16") {
    capacity = 24;
    map = cstr_int_map_alloc(capacity, allocator);

    must("create an empty heap allocated map");
      verify(map.length == 0);
      verify(map.keys.allocator == spec_allocator);

    must("enforce the map capacity to the next power of 2 of the given capacity");
      verify(map.keys.capacity == next_pow2(capacity));

    success();
  } end();
}
