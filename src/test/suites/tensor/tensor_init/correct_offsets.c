test( tensor_init, correct_offsets ) {

  given("a declined tensor");
    memory allocator = memory_init(0);
    tensor(i64) tns;


  when("providing an array with dimensions");
    array(u64)* dimensions = &array_of(u64, { 2, 3, 4, 5 });


  calling("tensor_init()");
    tns = tensor_init(i64)(dimensions, &allocator);


  must("initialize the tensor with the correct offsets");
    array_iterator(u64) offset = { 0 };
    for array_each(tns.offsets, offset) {
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
    memory_release(&allocator);
}
