spec( map_alloc ) {

  argument(int capacity);
  argument(memory* allocator);

  precondition("a valid key type");
  precondition("a valid value type");
    #define valid_key_type char*
    #define valid_value_type int

  precondition("a valid allocator")
    allocator = spec_allocator;

  when("the capacity is less than 16") {
    capacity = 12;
    map<char*, int>* map = map_alloc(valid_key_type, valid_value_type, capacity, allocator);

    must("create an empty heap allocated map");
      verify(map->length == 0);
      verify(map->keys.length == 0);
      verify(map->keys.allocator == spec_allocator);

    must("enforce the map capacity to 16");
      verify(map->keys.capacity == 16);

    success();
  }

  when("the capacity is greater than 16") {
    capacity = 24;

    must("create an empty heap allocated map");
      map<char*, int>* map = map_alloc(valid_key_type, valid_value_type, capacity, allocator);
      verify(map->length == 0);
      verify(map->keys.length == 0);
      verify(map->keys.allocator == spec_allocator);

    must("enforce the map capacity to the next power of 2 of the given capacity");
      verify(map->keys.capacity == next_pow2(capacity));

    success();
  }

  #undef valid_key_type
  #undef valid_value_type
  #undef valid_allocator
}
