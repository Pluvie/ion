spec( map_has ) {

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
      bool result = map_has(map, key);

      must("not fail");
        verify(error.occurred == false);

      must("return true");
        verify(result == true);

      success();
    } end();

    when("the key is not present in the map") {
      key = "f";
      apply(stack_allocated_map_condition);
      bool result = map_has(map, key);

      must("not fail");
        verify(error.occurred == false);

      must("return false");
        verify(result == false);

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
      bool result = map_has(map, key);

      must("not fail");
        verify(error.occurred == false);

      must("return true");
        verify(result == true);

      success();
    } end();

    when("the key is not present in the map") {
      key = "f";
      apply(heap_allocated_map_condition);
      bool result = map_has(map, key);

      must("not fail");
        verify(error.occurred == false);

      must("return false");
        verify(result == false);

      success();
    } end();
  } end();
  #undef heap_allocated_map_condition
}
