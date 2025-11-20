#include "map_del.h"

spec( map_del ) {
  argument(struct cstr_int_map* map);
  argument(char* key);
  returns(int* result);

  precondition("a valid map");
    #define preconditions \
      map = arena_push(spec_allocator, sizeof(*map)); \
      *map = cstr_int_map_alloc(16, spec_allocator); \
      cstr_int_map_set(map, "a", 7); \
      cstr_int_map_set(map, "b", 8); \
      cstr_int_map_set(map, "c", 9);

  {
    int original_map_length;
    int original_map_capacity;

    when("the key is present in the map") {
      key = "a";
      apply(preconditions);
      original_map_length = map->length;
      original_map_capacity = map->keys.capacity;
      result = cstr_int_map_del(map, key);

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
      apply(preconditions);
      original_map_length = map->length;
      original_map_capacity = map->keys.capacity;
      result = cstr_int_map_del(map, key);

      must("leave the map length unchanged");
        verify(map->length == original_map_length);

      must("return nullptr");
        verify(result == nullptr);

      must("leave the map capacity unchanged");
        verify(map->keys.capacity == original_map_capacity);

      success();
    } end();
  }
}
