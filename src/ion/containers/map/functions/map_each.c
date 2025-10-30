bool container_function(N, each) (
    struct N* map,
    struct iterator* iter,
    K** key_ptr,
    V** value_ptr
)
{
  if (iter->initialized) {
    iter->position++;
  } else {
    /* Unsigned integer overflow is well defined behaviour. When the first key of
      the map will be found, this index shall be incremented by 1, wrapping to 0.
      See: https://en.wikipedia.org/wiki/Integer_overflow */
    iter->index = (uint) -1;
    iter->initialized = true;
  }

  for (; iter->position < map->keys.capacity; iter->position++) {
    if (set_pos_is_free(&map->keys, iter->position))
      continue;

    iter->index++;
    *key_ptr = map->keys.data + iter->position;
    *value_ptr = map->values + iter->position;
    return true;
  }

  return false;
}
