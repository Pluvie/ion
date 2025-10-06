set<T> set<T>_init (
    unsigned int capacity,
    T* data,
    unsigned int* hashes
)
{
  return (set<T>) {
    .data = data,
    .hashes = hashes,
    .capacity = capacity,
    .load_limit = capacity,
  };
}
