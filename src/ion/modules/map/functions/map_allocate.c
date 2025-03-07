#ifdef ION_INCLUDED
static inline
#endif

struct map* map_allocate (
    u64 key_typesize,
    u64 value_typesize,
    u64 initial_capacity,
    struct memory* allocator
)
{
  struct map* map = memory_alloc_zero(allocator, sizeof(struct map));
  *map = map_init(key_typesize, value_typesize, initial_capacity, allocator);
  return map;
}
