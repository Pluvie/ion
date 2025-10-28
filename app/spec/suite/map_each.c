#include "map_each.h"

spec( map_each ) {
  argument(struct iterator* iter);
  argument(struct cstr_int_map* map);
  argument(cstr** key_ptr);
  argument(int** value_ptr);
  returns(bool result);

  precondition("an initialized iterator");
  precondition("a valid map");
  precondition("a valid key pointer");
  precondition("a valid value pointer");
    #define preconditions \
      iter = allocator_push(spec_allocator, sizeof(*iter)); \
      memory_set(iter, 0, sizeof(*iter)); \
      map = allocator_push(spec_allocator, sizeof(*map)); \
      *map = cstr_int_map_init(8, keys, values, hashes); \
      cstr_int_map_set(map, "a", 1); \
      cstr_int_map_set(map, "b", 2); \
      cstr_int_map_set(map, "c", 3); \
      key_ptr = &key; value_ptr = &value;

  {
    cstr* key;
    int* value;
    struct { cstr key; uint position; } key_positions[3] = { 0 };
    apply(preconditions);

    /* Find the keys in the map, and sort them by their position. This will be the
      order in which the `cstr_int_map_each` function shall scan them. */
    key_positions[0].key = "a";
    key_positions[0].position = cstr_int_map_keys_pos(&(map->keys), "a");
    key_positions[1].key = "b";
    key_positions[1].position = cstr_int_map_keys_pos(&(map->keys), "b");
    key_positions[2].key = "c";
    key_positions[2].position = cstr_int_map_keys_pos(&(map->keys), "c");
    qsort(key_positions, 3, sizeof(*key_positions), sort_by_position);

    must("iterate over all entries of the map using the provided iterator");
      result = cstr_int_map_each(map, iter, key_ptr, value_ptr);
      verify(result == true);
      verify(iter->index == 0);
      verify(iter->position == key_positions[0].position);
      verify(cstr_equal(*key, key_positions[0].key));
      verify(*value == *cstr_int_map_get(map, key_positions[0].key));

      result = cstr_int_map_each(map, iter, key_ptr, value_ptr);
      verify(result == true);
      verify(iter->index == 1);
      verify(iter->position == key_positions[1].position);
      verify(cstr_equal(*key, key_positions[1].key));
      verify(*value == *cstr_int_map_get(map, key_positions[1].key));

      result = cstr_int_map_each(map, iter, key_ptr, value_ptr);
      verify(result == true);
      verify(iter->index == 2);
      verify(iter->position == key_positions[2].position);
      verify(cstr_equal(*key, key_positions[2].key));
      verify(*value == *cstr_int_map_get(map, key_positions[2].key));

      result = cstr_int_map_each(map, iter, key_ptr, value_ptr);
      verify(result == false);

    success();
  }
}
