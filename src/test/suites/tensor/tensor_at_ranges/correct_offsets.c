test( tensor_at_ranges, correct_offsets ) {

  given("a struct tensor");
    struct memory allocator = memory_init(0);
    struct tensor tensor = tensor_init(
      sizeof(i32), &vector_of(u64, { 1, 2, 3, 4 }), &allocator);


  when("providing a vector with ranges");
    struct vector ranges = vector_of(struct range, {
      { .min = 0, .max = 0, .at = 0, }, 
      { .min = 0, .max = 1, .at = 1, },
      { .min = 1, .max = 2, .at = 2, },
      { .min = 0, .max = 3, .at = 2, },
    });


  calling("tensor_at_ranges()");
    void* position = tensor_at_ranges(&tensor, &ranges);


  must("correctly retrieve the tensor position determined by the ranges");
    u64 offsets[4] = {
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 0))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 1))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 2))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 3))->offset,
    };
    u64 offsets_multiplicators[4] = {
      offsets[0] == 0 ? 1 : offsets[0],
      offsets[1] == 0 ? 1 : offsets[1],
      offsets[2] == 0 ? 1 : offsets[2],
      offsets[3] == 0 ? 1 : offsets[3],
    };

    verify(position != NULL);
    verify((position - tensor.data) / sizeof(i32) ==
      0 * offsets_multiplicators[0] +
      1 * offsets_multiplicators[1] +
      2 * offsets_multiplicators[2] +
      2 * offsets_multiplicators[3]);


  success();
    memory_release(&allocator);
}
