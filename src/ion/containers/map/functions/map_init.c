map<K, V> map<K, V>_init (
    unsigned int capacity,
    K* keys,
    V* values,
    unsigned int* hashes
)
{
  return (map<K, V>) {
    .keys = set<K>_init(capacity, keys, hashes),
    .values = values,
  };
}
