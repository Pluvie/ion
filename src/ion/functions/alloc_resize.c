void* alloc_resize (
    void* old_address,
    int original_amount,
    int resized_amount
)
{
  void* new_address = alloc(resized_amount);
  byte_copy(new_address, old_address, original_amount);
  alloc_release(old_address);
  return new_address;
}
