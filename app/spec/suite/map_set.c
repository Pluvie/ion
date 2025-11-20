#include "map_set.h"

spec( map_set ) {
  argument(struct cstr_int_map* map);
  argument(cstr key);
  argument(int value);
  returns(uint result);

  when("the map is not allocated") {
    #define unallocated_map_condition \
      unallocated_map_init(); \
      map = &unallocated_map;

    uint original_map_length;
    uint original_map_capacity;

    when("the map length is inferior to its load limit") {
      #define map_under_load_limit_condition \
        cstr_int_map_set(map, "a", 7); \
        cstr_int_map_set(map, "b", 8); \
        cstr_int_map_set(map, "c", 9);

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(unallocated_map_condition);
        apply(map_under_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

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
        apply(unallocated_map_condition);
        apply(map_under_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

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
    #undef map_under_load_limit_condition

    /* when("the map is not allocated") */
    when("the map length is equal or greater than its load limit") {
      #define map_over_load_limit_condition \
        cstr_int_map_set(map, "a", 1); \
        cstr_int_map_set(map, "b", 2); \
        cstr_int_map_set(map, "c", 3); \
        cstr_int_map_set(map, "d", 4); \
        cstr_int_map_set(map, "e", 5); \
        cstr_int_map_set(map, "f", 6); \
        cstr_int_map_set(map, "g", 7); \
        cstr_int_map_set(map, "h", 8);

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(unallocated_map_condition);
        apply(map_over_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

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
        apply(unallocated_map_condition);
        apply(map_over_load_limit_condition);
        cstr_int_map_set(map, key, value);

        must("fatally fail with a specific message");
          verify(cstr_equal(sim.fatal, "map_set: stack allocated map is full"));

        success();
      } end();
    } end();
    #undef map_over_load_limit_condition
  } end();

  when("the map is allocated") {
    #define allocated_map_condition \
      map = arena_push(spec_allocator, sizeof(*map)); \
      *map = cstr_int_map_alloc(16, spec_allocator); \

    uint original_map_length;
    uint original_map_capacity;

    when("the map length is inferior to its load limit") {
      #define map_under_load_limit_condition \
        cstr_int_map_set(map, "a", 7); \
        cstr_int_map_set(map, "b", 8); \
        cstr_int_map_set(map, "c", 9);

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(allocated_map_condition);
        apply(map_under_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

        must("return a valid inserted position");
          verify(result != (uint) -1);

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
        apply(allocated_map_condition);
        apply(map_under_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

        must("return a valid inserted position");
          verify(result != (uint) -1);

        must("insert the value at that position");
          verify(map->values[result] == value);

        must("increase the map length by one");
          verify(map->length == original_map_length + 1);

        must("leave the map capacity unchanged");
          verify(map->keys.capacity == original_map_capacity);

        success();
      } end();
    } end();

    /* when("the map is allocated") */
    when("the map length is equal or greater than its load limit") {
      #define map_over_load_limit_condition \
        { int i; \
          cstr keys[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k" }; \
          int values[] = {  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11 }; \
          for (i = 0; i < map->keys.load_limit; i++) \
          cstr_int_map_set(map, keys[i], values[i]); } \

      when("the key is present in the map") {
        key = "a";
        value = 10;
        apply(allocated_map_condition);
        apply(map_over_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

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
        apply(allocated_map_condition);
        apply(map_over_load_limit_condition);
        original_map_length = map->length;
        original_map_capacity = map->keys.capacity;
        result = cstr_int_map_set(map, key, value);

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
  } end();
}
