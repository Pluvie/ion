void* alloc_resize_zero (
    void* old_address,
    int original_amount,
    int resized_amount
)
{
  void* new_address = alloc_zero(resized_amount);
  byte_copy(new_address, old_address, original_amount);
  free(old_address);
  return new_address;
}
