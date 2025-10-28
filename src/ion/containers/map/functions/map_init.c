struct N container_function(N, init) (
    uint capacity,
    K* keys,
    V* values,
    uint* hashes
)
{
  struct S set = container_function(S, init)(capacity, keys, hashes);
  struct N map = { 0 };
  map.keys = set;
  map.values = values;
  return map;
}
