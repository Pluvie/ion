set<T> set<T>_init (
    int capacity,
    T* data,
    int* hashes
)
{
  return (set<T>) {
    .data = data,
    .hashes = hashes,
    .capacity = capacity,
    .load_limit = capacity,
  };
}
