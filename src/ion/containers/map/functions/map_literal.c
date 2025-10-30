struct N container_function(N, literal) (
    K* keys,
    V* values,
    uint* hashes,
    uint capacity
)
{
  struct N map = { 0 };

  map.keys = container_function(S, literal)(keys, hashes, capacity);
  map.values = values;
  map.length = capacity;

  return map;
}
