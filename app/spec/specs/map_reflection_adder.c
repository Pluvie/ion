#include "map_reflection_adder.h"

spec( map_reflection_adder ) {
  argument(void* generic_map);
  argument(void* generic_key);

  precondition("a valid map");
    map<char*, int> map = map_alloc(char*, int, 8, spec_allocator);
    map_set(&map, "a", 3);
    map_set(&map, "b", 4);
    generic_map = &map;

  precondition("a valid key")
    char* key = "c"; generic_key = &key;

  must("behave exactly like map_set");
    map<char*, int> map_with_add = map_alloc(char*, int, 8, spec_allocator);
    map_set(&map_with_add, "a", 3);
    map_set(&map_with_add, "b", 4);

    void* result = map<char*, int>_reflection_adder(generic_map, generic_key);
    unsigned int map_result = (int*) result - map.values;
    unsigned int map_with_add_result = map_set(&map_with_add, key, 5);

    verify(map_result == map_with_add_result);
    verify(map.length == map_with_add.length);
    verify(map.keys.capacity == map_with_add.keys.capacity);
    verify(map.keys.allocator == map_with_add.keys.allocator);

  success();
}
