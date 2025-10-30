struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
)
{
  struct N map = { 0 };
  map.keys = container_function(S, alloc)(initial_capacity, allocator);
  map.values = allocator_push(allocator, map.keys.capacity * sizeof(V));
  memory_set(map.values, 0, map.keys.capacity * sizeof(K));
  return map;
}
