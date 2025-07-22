spec( map_set ) {

  argument(map<char*, int>* map);
  argument(char* key);
  argument(int value);

  when("the map is stack allocated") {
    #define stack_allocated_map_condition \
      map<char*,int> stack_map = map_init(char*, int, 16); \
      map = &stack_map; \
      map_set(map, "a", 7); \
      map_set(map, "b", 8); \
      map_set(map, "c", 9);

    when("the key is present in the map") {
      key = "a";
      value = 10;
      apply(stack_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int result = map_set(map, key, value);

      must("not fail");
        verify(error.occurred == false);

      must("return a valid inserted position");
        verify(result > 0);

      must("overwrite the previous value at that position");
        verify(map->values[result] == value);

      must("leave the map length unchanged");
        verify(map->length == original_map_length);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    }

    or_when("the key is not present in the map") {
      key = "f";
      apply(stack_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int result = map_set(map, key, value);

      must("not fail");
        verify(error.occurred == false);

      must("return a valid inserted position");
        verify(result > 0);

      must("insert the value at that position");
        verify(map->values[result] == value);

      must("increase the map length by one");
        verify(map->length == original_map_length + 1);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    }
  }
  #undef stack_allocated_map_condition

  or_when("the map is heap allocated") {
    #define heap_allocated_map_condition \
      map<char*, int>* map = map_alloc(char*, int, 16, spec_allocator); \
      map_set(map, "a", 7); \
      map_set(map, "b", 8); \
      map_set(map, "c", 9);

    when("the key is present in the map") {
      key = "a";
      apply(heap_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int result = map_set(map, key, value);

      must("not fail");
        verify(error.occurred == false);

      must("return a valid inserted position");
        verify(result > 0);

      must("overwrite the previous value at that position");
        verify(map->values[result] == value);

      must("leave the map length unchanged");
        verify(map->length == original_map_length);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    }

    or_when("the key is not present in the map") {
      key = "f";
      apply(heap_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int result = map_set(map, key, value);

      must("not fail");
        verify(error.occurred == false);

      must("return a valid inserted position");
        verify(result > 0);

      must("insert the value at that position");
        verify(map->values[result] == value);

      must("increase the map length by one");
        verify(map->length == original_map_length + 1);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    }
  }
  #undef heap_allocated_map_condition
}
