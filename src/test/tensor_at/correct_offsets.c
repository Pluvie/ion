test( tensor_at, correct_offsets ) {

  given("a struct tensor");
    struct memory allocator = memory_init(0);
    struct tensor tensor = tensor_init(
      sizeof(i32), &vector_of(u64, { 1, 2, 3, 4 }), &allocator);


  when("providing a vector with positions");
    struct vector positions = vector_of(u64, { 0, 1, 2, 2, });


  calling("tensor_at()");
    void* position = tensor_at(&tensor, &positions);

  must("correctly retrieve the tensor position determined by the positions");
    u64 offsets[4] = {
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 0))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 1))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 2))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 3))->offset,
    };
    
    verify(position != NULL);
    verify((position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 2*offsets[2] + 2*offsets[3]);

  success();
    memory_release(&allocator);
}