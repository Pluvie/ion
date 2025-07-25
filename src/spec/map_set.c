spec( map_set ) {

  argument(map<char*, int>* map);
  argument(char* key);
  argument(int value);

  when("the map is stack allocated") {
    #define stack_allocated_map_condition \
      map<char*, int> stack_map = map_init(char*, int, 8); \
      map = &stack_map;

    when("the map length is inferior to its load limit") {
      #define map_length_condition \
        map_set(map, "a", 1); \
        map_set(map, "b", 2); \
        map_set(map, "c", 3);

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(stack_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("overwrite the previous value at that position");
          verify(map->values[result] == value);

        must("leave the map length unchanged");
          verify(map->length == original_map_length);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();

      when("the key is not present in the map") {
        key = "z";
        apply(stack_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("insert the value at that position");
          verify(map->values[result] == value);

        must("increase the map length by one");
          verify(map->length == original_map_length + 1);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();
    } end();
    #undef map_length_condition

    // in: "the map is stack allocated"
    when("the map length is equal or greater than its load limit") {
      #define map_length_condition \
        map_set(map, "a", 1); \
        map_set(map, "b", 2); \
        map_set(map, "c", 3); \
        map_set(map, "d", 4); \
        map_set(map, "e", 5); \
        map_set(map, "f", 6); \
        map_set(map, "g", 7); \
        map_set(map, "h", 8);

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(stack_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("overwrite the previous value at that position");
          verify(map->values[result] == value);

        must("leave the map length unchanged");
          verify(map->length == original_map_length);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();

      when("the key is not present in the map") {
        key = "z";
        apply(stack_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("fail with a specific error");
          verify(error.occurred == true);
          verify(streq(error.message, "set: stack allocated map is full"));

        must("return -1");
          verify(result == -1);

        must("leave the map length unchanged");
          verify(map->length == original_map_length);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();
    } end();
    #undef map_length_condition
  } end();
  #undef stack_allocated_map_condition

  when("the map is heap allocated") {
    #define heap_allocated_map_condition \
      map<char*, int>* map = map_alloc(char*, int, 16, spec_allocator); \
      map_set(map, "a", 7); \
      map_set(map, "b", 8); \
      map_set(map, "c", 9);

    when("the map length is inferior to its load limit") {
      #define map_length_condition \
        map_set(map, "a", 1); \
        map_set(map, "b", 2); \
        map_set(map, "c", 3);

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(heap_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("overwrite the previous value at that position");
          verify(map->values[result] == value);

        must("leave the map length unchanged");
          verify(map->length == original_map_length);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();

      when("the key is not present in the map") {
        key = "z";
        apply(heap_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("insert the value at that position");
          verify(map->values[result] == value);

        must("increase the map length by one");
          verify(map->length == original_map_length + 1);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();
    } end();
    #undef map_length_condition

    // in: "the map is heap allocated"
    when("the map length is equal or greater than its load limit") {
      #define map_length_condition \
        char* keys[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k" }; \
        int values[] = {  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11 }; \
        for (int i = 0; i < map->keys.load_limit; i++) \
          map_set(map, keys[i], values[i]); \

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(heap_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("overwrite the previous value at that position");
          verify(map->values[result] == value);

        must("leave the map length unchanged");
          verify(map->length == original_map_length);

        must("increase the map capacity by a factor 2");
          verify(map->keys.capacity == 2 * original_map_capacity);

        success();
      } end();

      when("the key is not present in the map") {
        key = "z";
        apply(heap_allocated_map_condition);
        apply(map_length_condition);
        int original_map_length = map->length;
        int original_map_capacity = map->keys.capacity;
        int result = map_set(map, key, value);

        must("not fail");
          verify(error.occurred == false);

        must("return a valid inserted position");
          verify(result >= 0);

        must("insert the value at that position");
          verify(map->values[result] == value);

        must("increase the map length by one");
          verify(map->length == original_map_length + 1);

        must("increase the map capacity by a factor 2");
          verify(map->keys.capacity == 2 * original_map_capacity);

        success();
      } end();
    } end();
    #undef map_length_condition
  } end();
  #undef heap_allocated_map_condition
}
