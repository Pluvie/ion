t* tensor_at(t) (
    tensor(t)* tns,
    array(u64)* positions
)
{
  u64 final_offset = 0;

  array_iterator(u64) offset = { 0 };
  for array_each(tns->offsets, offset) {
    u64 position = as(u64, array_get(u64)(positions, offset.index));
    u64 offset_multiplicator = *offset.value;
    if (offset_multiplicator == 0)
      offset_multiplicator= 1;

    final_offset += position * offset_multiplicator;
  }

  return tns->data + final_offset;
}
