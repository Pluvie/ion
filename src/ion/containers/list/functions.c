list<T> list<T>_init (
    int capacity,
    T* data
)
{
  return (list<T>) {
    .data = data,
    .capacity = capacity,
  };
}
