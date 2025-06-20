map<K, V> map<K, V>_literal (
    int capacity,
    K* keys,
    V* values,
    int* hashes,
    void* pairs
)
{
  struct { K key; V value; }* key_value_pairs = pairs;

  for (int i = 0; i < capacity; i++) {
    K key = key_value_pairs[i].key;
    V value = key_value_pairs[i].value;
    keys[i] = key;
    values[i] = value;
  }

  map<K, V> map = {
    .keys = set<K>_literal(capacity, keys, hashes),
    .values = values,
    .length = capacity,
  };

  return map;
}
