set<T> set<T>_literal (
    unsigned int capacity,
    T* data,
    unsigned int* empty_hashes
)
{
  set<T> set = {
    .data = data,
    .hashes = empty_hashes,
    .capacity = capacity,
    .load_limit = capacity,
    .length = capacity,
  };

  for (int i = 0; i < capacity; i++)
#ifdef set_hash_function
    set_pos_occupy(&set, i, set_hash_function(data[i]));
#else
    set_pos_occupy(&set, i, hash_djb2(data + i, sizeof(T)));
#endif

  return set;
}
