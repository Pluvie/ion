map(kt, vt)* map_(allocate, kt, vt) (
    u64 initial_capacity,
    memory* allocator
)
{
  map(kt, vt)* m = memory_alloc(allocator, sizeof(map(kt, vt)));
  *m = map_(init, kt, vt)(initial_capacity, allocator);
  return m;
}
