void* memory_alloc (
    memory* allocator,
    int amount
)
{
  /* Defines the default alignment of memory allocations. A 32bit alignment is chosen,
   * in order to facilitate the use of SIMD instructions. */
  #define default_alignment 32

  /* If the memory has already some allocated data, before allocating a new one check
   * whether it must grow to make space for the new data. */
  if (allocator->position > 0)
    goto grow_check;

  /* If the memory does not have any allocated data, check if the requested amount is 
   * greater than the memory capacity: if so, increase the capacity to the amount. */
  if (amount > allocator->capacity)
    allocator->capacity = next_pow2(amount);

  /* Create the allocator data and allocate the requested amount. */
  allocator->data = alloc_aligned(allocator->capacity, default_alignment);
  goto allocate;

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

  allocator->regions.addresses = alloc_aligned(
    allocator->regions.capacity * sizeof(void*), default_alignment);

  goto append_region;

regions_grow_check:
  /* The regions have reached capacity: extend their capacity and reallocate them. */
  if (allocator->regions.count < allocator->regions.capacity)
    goto append_region;

  int regions_new_capacity = allocator->regions.capacity * 2;
  void* regions_new_addresses = alloc_aligned(
    regions_new_capacity * sizeof(void*), default_alignment);
  byte_copy(regions_new_addresses,
    allocator->regions.addresses,
    allocator->regions.capacity * sizeof(void*));
  alloc_release(allocator->regions.addresses);
  allocator->regions.capacity = regions_new_capacity;
  allocator->regions.addresses = regions_new_addresses;

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

  allocator->data = alloc_aligned(allocator->capacity, default_alignment);

allocate:
  void* address = allocator->data + allocator->position;
  allocator->position += amount;
  allocator->allocations.size += amount;
  allocator->allocations.count++;
  return address;

  #undef default_alignment
}
