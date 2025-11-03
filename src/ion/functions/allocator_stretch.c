void* allocator_stretch (
    struct allocator* allocator,
    uint amount
)
{
  byte* address;
  uint new_capacity;
  struct allocator_line* line = &(allocator->line);

  if (line->data == nullptr)
    goto empty_line;
  else if (line->position + amount <= line->capacity)
    goto extendable_line;
  else
    goto reallocate_line;

empty_line:
  if (amount > line->capacity)
    line->capacity = next_pow2(amount);

  line->data = memory_acquire(line->capacity);
  goto terminate;

extendable_line:
  goto terminate;

reallocate_line:
  new_capacity = 2*line->capacity;
  if (amount > new_capacity)
    new_capacity = next_pow2(amount);

  line->data = memory_resize(line->data, new_capacity);
  line->capacity = new_capacity;

terminate:
  line->position += amount;
  address = line->data + line->position;
  allocator->allocations.size += amount;
  allocator->allocations.count++;
  return address;
}
