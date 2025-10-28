struct N container_function(N, init) (
    uint capacity,
    T* data,
    uint* hashes
)
{
  struct N set = { 0 };
  set.data = data;
  set.hashes = hashes;
  set.capacity = capacity;
  set.load_limit = capacity;
  return set;
}
