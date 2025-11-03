void* allocator_push (
    struct allocator* allocator,
    uint amount
)
{
  uint new_capacity, regions_new_capacity;
  void *address, *region_address, *regions_new_addresses;
  struct allocator_arena* arena = &(allocator->arena);

  /* If the allocator has already some allocated data, before allocating a new one check
    whether it must grow to make space for the new data. */
  if (arena->position > 0)
    goto grow_check;

  /* If the allocator does not have any allocated data, check if the requested amount is 
    greater than the allocator capacity: if so, increase the capacity to the next
    power of two starting from amount. */
  if (amount > arena->capacity)
    arena->capacity = next_pow2(amount);

  /* Create the allocator data and allocate the requested amount.  */
  arena->data = memory_acquire(arena->capacity);
  goto allocate;

grow_check:
  /* If the allocator has enough capacity to fit the requested amount, then allocate
    directly. */
  if (arena->position + amount <= arena->capacity)
    goto allocate;

  /* The allocator has reached the capacity. Create a new region to remember previously
    allocated data. */
  if (arena->regions.addresses != nullptr)
    goto regions_grow_check;
  else
    goto initialize_regions;

initialize_regions:
  /* The regions were not yet initialized. */
  if (arena->regions.capacity <= 0)
    arena->regions.capacity = 8;

  arena->regions.addresses = memory_acquire(arena->regions.capacity * sizeof(void*));
  goto append_region;

regions_grow_check:
  /* The regions have reached capacity: extend their capacity and reallocate them. */
  if (arena->regions.count < arena->regions.capacity)
    goto append_region;

  regions_new_capacity = arena->regions.capacity * 2;
  regions_new_addresses = memory_acquire(regions_new_capacity * sizeof(void*));
  memory_copy(regions_new_addresses, arena->regions.addresses, arena->regions.capacity * sizeof(void*));
  memory_release(arena->regions.addresses);
  arena->regions.capacity = regions_new_capacity;
  arena->regions.addresses = regions_new_addresses;

append_region:
  /* Remember the current allocator address as last region. */
  region_address = arena->data;
  arena->regions.addresses[arena->regions.count] = region_address;
  arena->regions.count++;
  arena->position = 0;
  goto increase_capacity;

increase_capacity:
  /* Increase the allocator capacity: if the amount is greater than double the current
    capacity, use it to calculate a new fitting capacity. Otherwise, just double the
    previous capacity. */
  new_capacity = arena->capacity * 2;
  if (amount > new_capacity)
    new_capacity = next_pow2(amount);

  arena->capacity = new_capacity;
  arena->data = memory_acquire(arena->capacity);

allocate:
  address = arena->data + arena->position;
  arena->position += amount;
  allocator->allocations.size += amount;
  allocator->allocations.count++;
  return address;
}
