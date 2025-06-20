set<T> set<T>_literal (
    int capacity,
    T* data,
    int* empty_hashes
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
    set_pos_occupy(&set, i, hash(data[i]));

  return set;
}
