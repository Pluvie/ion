test( tensor_init, correct_length ) {

  given("a struct tensor");
    struct tensor tensor;
    struct memory allocator = memory_init(0);


  when("providing a vector with dimensions");
    struct vector dimensions = vector_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tensor = tensor_init(sizeof(i32), &dimensions, &allocator);


  must("initialize the tensor with the correct length");
    verify(tensor.length == 2 * 3 * 4 * 5);


  success();
    memory_release(&allocator);
}
