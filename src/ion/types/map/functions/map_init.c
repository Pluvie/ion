map<K, V> map<K, V>_init (
    int capacity,
    K* keys,
    V* values,
    int* hashes
)
{
  return (map<K, V>) {
    .keys = set<K>_init(capacity, keys, hashes),
    .values = values,
  };
}
