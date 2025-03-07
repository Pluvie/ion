#ifdef ION_INCLUDED
static inline
#endif

void* memory_alloc (
    struct memory* allocator,
    u64 amount
)
{
  i32 os_result;

init_check:
  if (allocator->position > 0)
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
  if (allocator->position + amount <= allocator->capacity)
    goto allocate;

  struct { void* address; u64 capacity; } region =
    { allocator->data, allocator->capacity };

  if (allocator->regions == NULL) {
    if (allocator->regions_capacity < MEMORY_MIN_REGIONS)
      allocator->regions_capacity = MEMORY_MIN_REGIONS;

    allocator->regions = malloc(allocator->regions_capacity * sizeof(region));

    if (unlikely(allocator->regions == NULL)) {
      os_result = ENOMEM;
      goto os_error;
    }
  } else if (allocator->regions_count >= allocator->regions_capacity) {
    allocator->regions_capacity *= 2;
    allocator->regions = realloc(allocator->regions,
      allocator->regions_capacity * sizeof(region));
  }

  memcpy(allocator->regions + allocator->regions_count, &region, sizeof(region));
  allocator->regions_count++;
  goto increase_capacity;

increase_capacity:
  if (amount > allocator->capacity)
    allocator->capacity = next_pow2(amount + allocator->capacity);
  else
    allocator->capacity *= 2;

  os_result = posix_memalign((void**) &(allocator->data),
    MEMORY_DEFAULT_ALIGN, allocator->capacity);

  if (likely(os_result) == 0)
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
  void* address = allocator->data + allocator->position;
  allocator->position += amount;
  allocator->allocations++;
  return address;
}
