#ifdef ION_INCLUDED
static inline
#endif

void* ring_alloc (
    struct ring* allocator,
    u64 amount
)
{
  i32 os_result;

init_check:
  if (allocator->data != NULL)
    goto grow_check;

  if (amount > allocator->capacity)
    allocator->capacity = next_pow2(amount);

  os_result = posix_memalign((void**) &(allocator->data),
    MEMORY_DEFAULT_ALIGN, allocator->capacity);

  if (likely(os_result) == 0)
    goto allocate;
  else
    goto os_error;

grow_check:
  if (allocator->free_space <= amount)
    goto allocate;

increase_capacity:
  void* new_data = NULL;
  u64 new_capacity = 0;

  if (amount > allocator->capacity)
    new_capacity = next_pow2(amount + allocator->capacity);
  else
    new_capacity = allocator->capacity * 2;

  os_result = posix_memalign((void**) &(new_data),
    MEMORY_DEFAULT_ALIGN, new_capacity);

  if (likely(os_result) == 0)
    goto copy_data;

copy_data:
  memcpy(new_data, allocator->data, allocator->capacity);
  free(allocator->data);
  allocator->capacity = new_capacity;
  allocator->data = new_data;
  allocator->junction = new_data + new_capacity;
  goto allocate;

os_error:
  switch (os_result) {
  case ENOMEM:
    fprintf(stderr, "fatal: %li, not enough memory\n", allocator->capacity);
    break;
  default:
    fprintf(stderr, "fatal: memalign returned %i\n", os_result);
    break;
  }
  abort();

allocate:
  void* result = NULL;

  if (allocator->end >= allocator->begin)
    goto allocate_before_junction;
  else
    goto allocate_after_junction;

allocate_before_junction:
  return result;

allocate_after_junction:
  result = allocator->data - allocator->end;
  allocator->end += amount;
  allocator->free_space -= amount;
  allocator->allocated_space += amount;
  return result;
}
