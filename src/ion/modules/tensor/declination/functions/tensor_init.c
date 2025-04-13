tensor(t) tensor_init(t) (
    array(u64)* dimensions,
    memory* allocator
)
{
  tensor(t) tns = { 0 };

  if (unlikely(dimensions->length == 0)) {
    fail("cannot initialize tensor: no dimensions given");
    return tns;
  }

  tns.length = 1;
  tns.allocator = allocator;
  tns.offsets = array_allocate(u64)(dimensions->length, allocator);

  array_iterator(u64) dimension = { 0 };
  for array_each(dimensions, dimension) {
    /**
     * For each input dimension, calculate the total tensor lenght by multiplying the
     * dimension length sequentially.
     *
     * Also, calculates each dimension offset by multiplying sequentially all its
     * next dimensions. The last dimension shall always have offset equal to 0. */
    tns.length *= *dimension.value;

    /* Last dimension has always offset equal to 0. */
    if (dimension.index == dimensions->length - 1) {
      array_push(u64)(tns.offsets, &(u64) { 0 });
      break;
    }

    /* Multiplies all subsequent dimensions length to calculate this dimension offset. */
    u64 offset = 1;

    array_iterator(u64) next_dimension = { .index = dimension.index + 1 };
    for array_each(dimensions, next_dimension)
      offset *= *next_dimension.value;

    array_push(u64)(tns.offsets, &offset);
  }

  tns.data = memory_alloc_zero(allocator, tns.length * sizeof(t));

  return tns;
}
