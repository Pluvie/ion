void* alloc_resize (
    void* old_address,
    int original_amount,
    int resized_amount
)
{
  void* new_address = alloc(resized_amount);
  memcpy(new_address, old_address, original_amount);
  free(old_address);
  return new_address;
}
