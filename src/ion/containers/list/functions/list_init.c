list<T> list<T>_init (
    unsigned int capacity,
    T* data
)
{
  return (list<T>) {
    .data = data,
    .capacity = capacity,
  };
}
