test( tensor_init, correct_dimensions ) {

  given("a declined tensor");
    tensor(i64) tensor;


  when("providing an array with dimensions");
    array(u64)* dimensions = &array_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tensor = tensor_init(i64)(dimensions, test_allocator);


  must("initialize the tensor with the correct dimensions");
    verify(tensor.offsets->length == dimensions->length);


  success();
}
