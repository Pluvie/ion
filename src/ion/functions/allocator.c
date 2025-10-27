struct allocator allocator_init (
    uint capacity
)
{
  struct allocator result = { 0 };
  result.capacity = next_pow2(capacity);
  return result;
}

void* allocator_pop (
    struct allocator* allocator,
    uint amount
)
{
  if (amount > allocator->position)
    allocator->position = 0;
  else
    allocator->position -= amount;

  return allocator->data + allocator->position;
}

void* allocator_push (
    struct allocator* allocator,
    uint amount
)
{
  uint new_capacity, regions_new_capacity;
  void *address, *region_address, *regions_new_addresses;

  /*
    If the allocator has already some allocated data, before allocating a new one check
    whether it must grow to make space for the new data.
  */
  if (allocator->position > 0)
    goto grow_check;

  /*
    If the allocator does not have any allocated data, check if the requested amount is 
    greater than the allocator capacity: if so, increase the capacity to the next
    power of two starting from amount.
  */
  if (amount > allocator->capacity)
    allocator->capacity = next_pow2(amount);

  /* Create the allocator data and allocate the requested amount.  */
  allocator->data = memory_acquire(allocator->capacity);
  goto allocate;

grow_check:
  /* If the allocator has enough capacity to fit the requested amount, allocate directly. */
  if (allocator->position + amount <= allocator->capacity)
    goto allocate;

  /* The allocator has reached the capacity. Create a new region to remember previously allocated data. */
  if (likely(allocator->regions.addresses != nullptr))
    goto regions_grow_check;
  else
    goto initialize_regions;

initialize_regions:
  /* The regions were not yet initialized. */
  if (allocator->regions.capacity <= 0)
    allocator->regions.capacity = 8;

  allocator->regions.addresses = memory_acquire(allocator->regions.capacity * sizeof(void*));
  goto append_region;

regions_grow_check:
  /* The regions have reached capacity: extend their capacity and reallocate them. */
  if (allocator->regions.count < allocator->regions.capacity)
    goto append_region;

  regions_new_capacity = allocator->regions.capacity * 2;
  regions_new_addresses = memory_acquire(regions_new_capacity * sizeof(void*));
  memory_copy(regions_new_addresses,
    allocator->regions.addresses,
    allocator->regions.capacity * sizeof(void*));
  memory_release(allocator->regions.addresses);
  allocator->regions.capacity = regions_new_capacity;
  allocator->regions.addresses = regions_new_addresses;

append_region:
  /* Remember the current allocator address as last region. */
  region_address = allocator->data;
  allocator->regions.addresses[allocator->regions.count] = region_address;
  allocator->regions.count++;
  allocator->position = 0;
  goto increase_capacity;

increase_capacity:
  /*
    Increase the allocator capacity: if the amount is greater than double the current
    capacity, use it to calculate a new fitting capacity. Otherwise, just double the
    previous capacity.
  */
  new_capacity = allocator->capacity * 2;
  if (amount > new_capacity)
    new_capacity = next_pow2(amount);

  allocator->capacity = new_capacity;
  allocator->data = memory_acquire(allocator->capacity);

allocate:
  address = allocator->data + allocator->position;
  allocator->position += amount;
  allocator->allocations.size += amount;
  allocator->allocations.count++;
  return address;
}

void allocator_release (
    struct allocator* allocator
)
{
  uint region_index;
  for (region_index = 0; region_index < allocator->regions.count; region_index++)
    memory_release(allocator->regions.addresses[region_index]);

  if (allocator->regions.addresses != nullptr)
    memory_release(allocator->regions.addresses);

  if (allocator->data != nullptr)
    memory_release(allocator->data);

  memory_set(allocator, 0, sizeof(*allocator));
}
