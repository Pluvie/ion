struct N container_function(N, literal) (
    T* data,
    uint* hashes,
    uint capacity
)
{
  struct N set = { 0 };
  uint i;

  set.data = data;
  set.length = capacity;
  set.capacity = capacity;
  set.load_limit = capacity;
  set.hashes = hashes;

  for (i = 0; i < capacity; i++)
    set_pos_occupy(&set, i, container_hasher(data[i]));

  return set;
}
