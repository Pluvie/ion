test( tensor_init, correct_dimensions ) {

  given("a declined tensor");
    memory allocator = memory_init(0);
    tensor(i64) tns;


  when("providing an array with dimensions");
    array(u64)* dimensions = &array_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tns = tensor_init(i64)(dimensions, &allocator);


  must("initialize the tensor with the correct dimensions");
    verify(tns.offsets->length == dimensions->length);


  success();
    memory_release(&allocator);
}
