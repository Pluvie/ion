typedef struct map<K, V> {
  set<K> keys;
  V* values;
  unsigned int length;
} map<K, V>;
check_sizeof(64, map<K, V>);
