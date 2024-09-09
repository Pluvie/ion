void* map_set (
    struct map* map,
    void* key,
    void* value
)
{
  /* In order to protect from double rehashing, the `map_set` function works as a
   * wrapper to the `map_set_rehash` function.
   *
   * This function takes an additional boolean argument, which indicates whether the
   * `map_set` function is being called within a rehash. If so, the rehash is aborted,
   * and a new one is reinitiated with double the capacity. */
  return map_set_rehash(map, key, value, false);
}
