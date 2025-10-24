#include "map_reflection_adder.h"

spec( map_reflection_adder ) {
  argument(void* generic_map);
  argument(void* generic_entry);

  precondition("a valid map");
    map<char*, int> map = map_alloc(char*, int, 8, spec_allocator);
    map_set(&map, "a", 3);
    map_set(&map, "b", 4);
    generic_map = &map;

  precondition("a valid entry") \
    char* entry_key = "c"; int entry_value = 5; \
    struct { char** key; int* value; } entry = { &entry_key, &entry_value }; \
    generic_entry = &entry;

  must("behave exactly like map_set");
    map<char*, int> map_with_add = map_alloc(char*, int, 8, spec_allocator);
    map_set(&map_with_add, "a", 3);
    map_set(&map_with_add, "b", 4);

    void* result = map<char*, int>_reflection_adder(generic_map, generic_entry);
    unsigned int map_result = (int*) result - map.values;
    unsigned int map_with_add_result = map_set(&map_with_add, entry_key, entry_value);

    verify(map_result == map_with_add_result);
    verify(map.length == map_with_add.length);
    verify(map.keys.capacity == map_with_add.keys.capacity);
    verify(map.keys.allocator == map_with_add.keys.allocator);

  success();
}
