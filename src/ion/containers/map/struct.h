typedef struct map<K, V> {
  set<K> keys;
  V* values;
  unsigned int length;
} map<K, V>;
