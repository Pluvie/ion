test( tensor_init, correct_offsets ) {

  given("a declined tensor");
    tensor(i64) tensor;


  when("providing an array with dimensions");
    array(u64)* dimensions = &array_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tensor = tensor_init(i64)(dimensions, test_allocator);


  must("initialize the tensor with the correct offsets");
    array_iterator(u64) offset = { 0 };
    for array_each(tensor.offsets, offset) {
      switch (offset.index) {
      case 0:
        verify(*offset.value == 3 * 4 * 5);
        break;
      case 1:
        verify(*offset.value == 4 * 5);
        break;
      case 2:
        verify(*offset.value == 5);
        break;
      case 3:
        verify(*offset.value == 0);
        break;
      }
    }


  success();
}
