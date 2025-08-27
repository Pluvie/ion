spec( map_del ) {

  argument(map<char*, int>* map);
  argument(char* key);

  when("the map is stack allocated") {
    #define stack_allocated_map_condition \
      map<char*, int> stack_map = map_init(char*, int, 16); \
      map = &stack_map; \
      map_set(map, "a", 7); \
      map_set(map, "b", 8); \
      map_set(map, "c", 9);

    when("the key is present in the map") {
      key = "a";
      apply(stack_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int* result = map_del(map, key);

      must("not fail");
        verify(failure.occurred == false);

      must("decrease the map length by 1");
        verify(map->length == original_map_length - 1);

      must("return the value associated with the key");
        verify(*result == 7);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    } end();

    when("the key is not present in the map") {
      key = "f";
      apply(stack_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int* result = map_del(map, key);

      must("not fail");
        verify(failure.occurred == false);

      must("leave the map length unchanged");
        verify(map->length == original_map_length);

      must("return null");
        verify(result == NULL);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    } end();
  } end();
  #undef stack_allocated_map_condition

  when("the map is heap allocated") {
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
      int* result = map_del(map, key);

      must("not fail");
        verify(failure.occurred == false);

      must("decrease the map length by 1");
        verify(map->length == original_map_length - 1);

      must("return the value associated with the key");
        verify(*result == 7);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    } end();

    when("the key is not present in the map") {
      key = "f";
      apply(heap_allocated_map_condition);
      int original_map_length = map->length;
      int original_map_capacity = map->keys.capacity;
      int* result = map_del(map, key);

      must("not fail");
        verify(failure.occurred == false);

      must("leave the map length unchanged");
        verify(map->length == original_map_length);

      must("return null");
        verify(result == NULL);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    } end();
  } end();
  #undef heap_allocated_map_condition
}
