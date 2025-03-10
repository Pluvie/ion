test( tensor_init, correct_dimensions ) {

  given("a struct tensor");
    struct tensor tensor;
    struct memory allocator = memory_init(0);


  when("providing a vector with dimensions");
    struct vector dimensions = vector_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tensor = tensor_init(sizeof(i32), &dimensions, &allocator);


  must("initialize the tensor with the correct dimensions");
    for vector_each(
        tensor.dimensions, struct tensor_dimension*, dimension, dimension_index)
      switch (dimension_index) {
      case 0:
        verify(dimension->length == 2);
        break;
      case 1:
        verify(dimension->length == 3);
        break;
      case 2:
        verify(dimension->length == 4);
        break;
      case 3:
        verify(dimension->length == 5);
        break;
      }


  success();
    memory_release(&allocator);
}
