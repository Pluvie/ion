map(kt, vt)* map_allocate(kt, vt) (
    u64 initial_capacity,
    memory* allocator
)
{
  map(kt, vt)* m = memory_alloc(allocator, sizeof(map(kt, vt)));
  *m = map_init(kt, vt)(initial_capacity, allocator);
  return m;
}
