test( tensor_init, correct_offsets ) {

  given("a struct tensor");
    struct tensor tensor;
    struct memory allocator = memory_init(0);


  when("providing a vector with dimensions");
    struct vector dimensions = vector_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tensor = tensor_init(sizeof(i32), &dimensions, &allocator);


  must("initialize the tensor with the correct offsets");
    for vector_each_with_index(
        tensor.dimensions, dimension_index, struct tensor_dimension*, dimension)
      switch (dimension_index) {
      case 0:
        verify(dimension->offset == 3 * 4 * 5);
        break;
      case 1:
        verify(dimension->offset == 4 * 5);
        break;
      case 2:
        verify(dimension->offset == 5);
        break;
      case 3:
        verify(dimension->offset == 0);
        break;
      }


  success();
    memory_release(&allocator);
}
