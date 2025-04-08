static inline bool map_key_equal (
    struct map* map,
    void* k1,
    void* k2
)
{
  if (map->key_typesize <= sizeof(u64))
    return (*(u64*) k1 == *(u64*) k2);
  else
    return memeq(k1, k2, map->key_typesize);
}
