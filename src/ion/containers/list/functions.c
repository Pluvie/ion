/*
struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
)
{
  uint capacity = initial_capacity;
  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  struct N list = { 0 };

  list.capacity = capacity;
  list.allocator = allocator;
  list.data = allocator_push(allocator, capacity * sizeof(T));
  memory_set(list.data, 0, capacity * sizeof(T));

  return list;
}
*/

T* container_function(N, at) (
    struct N* list,
    uint position
)
{
  if (position < list->length)
    return list->data + position;

  /*fatal(f(position), ": overbound list position");*/
  return nullptr;
}

/*
uint container_function(N, del) (
    struct N* list,
    T element
)
{
  T previous = { 0 };

  for(int i = list->length - 1; i >= 0; i--) {
  #ifdef list_eq_function
    if (list_eq_function(element, list->data[i])) {
  #else
    if (memory_equal((&element), list->data + i, sizeof(T))) {
  #endif
      memory_copy(list->data + i, &previous, sizeof(T));
      list->length--;
      return (uint) i;
    }

    T temp = { 0 };
    memory_copy(&temp, list->data + i, sizeof(T));
    memory_copy(list->data + i, &previous, sizeof(T));
    memory_copy(&previous, &temp, sizeof(T));
  }

  return (uint) -1;
}
enum bool container_function(N, each) (
    struct N* list,
    struct iterator* iter
)
{
  iter->gate = ~0;

  if (iter->position < list->length)
    return true;

  return false;
}
struct N container_function(N, init) (
    uint capacity,
    T* data
)
{
  return (struct N) {
    .data = data,
    .capacity = capacity,
  };
}
T* container_function(N, pop) (
    struct N* list
)
{
  if (list->length > 0)
    goto pop;

  fail("pop: empty list");
  return nullptr;

pop:
  T* element = list->data + list->length - 1;
  list->length--;
  return element;
}
*/

uint container_function(N, push) (
    struct N* list,
    T element
)
{
  uint position;
  T* extended_data;

  if (list->length < list->capacity)
    goto push;
  else
    goto grow;

grow:
  if (list->allocator == nullptr) {
    /*fatal("push: stack allocated list is full");*/
    return (uint) -1;
  }

  list->capacity *= 2;
  /*extended_data = allocator_push(list->allocator, list->capacity * sizeof(T));*/
  extended_data = malloc(list->capacity * sizeof(T));
  memset(extended_data, 0, list->capacity * sizeof(T));
  memcpy(extended_data, list->data, list->length * sizeof(T));
  list->data = extended_data;

push:
  position = list->length;
  list->data[list->length] = element;
  list->length++;
  return position;
}

/*
void container_function(sort) (
    struct N* list,
    int (*cmp_function)(T* v, T* u)
)
{
  qsort(list->data, list->length, sizeof(T),
    (int0 (*)(const void*, const void*)) cmp_function);
}
*/
