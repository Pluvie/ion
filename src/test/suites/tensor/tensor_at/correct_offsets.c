test( tensor_at, correct_offsets ) {

  given("a declined tensor");
    tensor(i64) tensor = tensor_init(i64)(
      &array_of(u64, { 2, 3, 4, 5 }), test_allocator);


  when("providing an array with positions");
    array(u64)* positions = &array_of(u64, { 1, 2, 3, 4 });


  calling("tensor_at()");
    i64* position = tensor_at(i64)(&tensor, positions);
    u64 position_offset = 0;


  must("correctly retrieve the tensor position determined by the positions");
    array_iterator(u64) iter = { 0 };
    for array_each(tensor.offsets, iter) {
      u64 offset = *iter.value;
      if (offset == 0) offset = 1;
      u64 position = as(u64, array_get(u64)(positions, iter.index));
      position_offset += position * offset;
    }

    verify(position != NULL);
    verify(position - tensor.data == position_offset);


  success();
}
