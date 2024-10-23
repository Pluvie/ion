#ifdef ION_INCLUDED
static inline
#endif

struct tensor tensor_init (
    u64 typesize,
    struct vector* input_dimensions,
    struct memory* allocator
)
{
initialize_length_and_dimensions:
  u64 tensor_length = 1;

  struct vector* dimensions = vector_allocate(
    sizeof(struct tensor_dimension), input_dimensions->length, allocator);

  /**
   * For each input dimension, calculate the total tensor lenght by multiplying the
   * dimension length sequentially.
   *
   * Also, calculates each dimension offset by multiplying sequentially all its
   * next dimensions. The last dimension shall always have offset equal to 0. */
  for vector_each_with_index(
      input_dimensions, input_dimension_index, u64*, input_dimension_length) {

    tensor_length *= *input_dimension_length;

    struct tensor_dimension dimension = {
      .length = *input_dimension_length,
      .offset = 0,
      .cursor = 0,
    };

    /* Last dimension has always offset equal to 0. */
    if (input_dimension_index == input_dimensions->length - 1) {
      vector_set(dimensions, input_dimension_index, &dimension);
      break;
    }

    /* Multiplies all subsequent dimensions length to calculate this dimension offset. */
    dimension.offset = 1;

    for (u32 next_dimension_index = input_dimension_index + 1;
        next_dimension_index < input_dimensions->length;
        next_dimension_index++) {
      u64 next_dimension_length = as(u64,
        vector_get(input_dimensions, next_dimension_index));
      dimension.offset *= next_dimension_length;
    }

    vector_set(dimensions, input_dimension_index, &dimension);
  }

initialize:
  struct tensor tensor = {
    .typesize = typesize,
    .length = tensor_length,
    .data = memory_alloc_zero(allocator, typesize * tensor_length),
    .dimensions = dimensions,
  };

  return tensor;
}
