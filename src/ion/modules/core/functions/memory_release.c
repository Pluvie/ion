#ifdef ION_INCLUDED
static inline
#endif

void memory_release (
    struct memory* allocator
)
{
  if (allocator->data != NULL)
    free(allocator->data);

  for (u64 i = 0; i < allocator->regions_count; i++)
    free(allocator->regions[i].address);

  if (allocator->regions != NULL)
    free(allocator->regions);

  memzero(allocator, sizeof(struct memory));
}
