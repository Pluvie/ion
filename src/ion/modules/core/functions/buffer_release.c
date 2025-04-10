void buffer_release (
    buffer* allocator
)
{
  if (allocator->data != NULL)
    free(allocator->data);

  memzero(allocator, sizeof(buffer));
}
