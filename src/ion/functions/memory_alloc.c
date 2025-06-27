void* memory_alloc (
    memory* allocator,
    int amount
)
{
  int os_result;

  /* If the memory has already some allocated data, before allocating a new one check
   * whether it must grow to make space for the new data. */
  if (allocator->position > 0)
    goto grow_check;

  /* If the memory does not have any allocated data, check if the requested amount is 
   * greater than the memory capacity: if so, increase the capacity to the amount. */
  if (amount > allocator->capacity)
    allocator->capacity = next_pow2(amount);

  /* Create the allocator data and allocate the requested amount. */
  os_result = posix_memalign(&allocator->data, 32, allocator->capacity);

  if (likely(os_result) == 0)
    goto allocate;
  else
    goto os_error;

grow_check:
  /* If the memory has enough capacity to fit the requested amount, allocate directly. */
  if (allocator->position + amount <= allocator->capacity)
    goto allocate;

  /* The memory has reached the capacity. Create a new region to remember previously
   * allocated data. */
  if (likely(allocator->regions.addresses != NULL))
    goto regions_grow_check;
  else
    goto initialize_regions;

initialize_regions:
  /* The regions were not yet initialized. */
  if (allocator->regions.capacity <= 0)
    allocator->regions.capacity = 8;

  allocator->regions.addresses = malloc(allocator->regions.capacity * sizeof(void*));
  if (unlikely(allocator->regions.addresses == NULL)) {
    os_result = ENOMEM;
    goto os_error;
  }

  goto append_region;

regions_grow_check:
  /* The regions have reached capacity: extend their capacity and reallocate them. */
  if (allocator->regions.count < allocator->regions.capacity)
    goto append_region;

  allocator->regions.capacity *= 2;
  allocator->regions.addresses = realloc(
    allocator->regions.addresses,
    allocator->regions.capacity * sizeof(void*));

append_region:
  /* Remember the current memory address as last region. */
  void* region_address = allocator->data;
  allocator->regions.addresses[allocator->regions.count] = region_address;
  allocator->regions.count++;
  allocator->position = 0;
  goto increase_capacity;

increase_capacity:
  /* Increase the memory capacity: if the amount is greater than the current capacity,
   * use it to calculate a new fitting capacity. Otherwise, just double the previous
   * capacity. */
  if (amount > allocator->capacity)
    allocator->capacity = next_pow2(amount + allocator->capacity);
  else
    allocator->capacity *= 2;

  os_result = posix_memalign(&allocator->data, 32, allocator->capacity);

  if (likely(os_result) == 0)
    goto allocate;

os_error:
  switch (os_result) {
  case ENOMEM:
    fatal("%li, not enough memory", allocator->capacity);
  default:
    fatal("memalign returned %li", os_result);
  }

allocate:
  void* address = allocator->data + allocator->position;
  allocator->position += amount;
  allocator->allocations.size += amount;
  allocator->allocations.count++;
  return address;
}
