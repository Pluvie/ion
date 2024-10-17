test( tensor_iterate, correct_positions ) {

  given("a struct tensor");
    struct memory allocator = memory_init(0);
    struct tensor tensor = tensor_init(
      sizeof(i32), &vector_of(u64, { 1, 2, 3, 4 }), &allocator);


  when("providing a vector with positions");
    struct vector positions = vector_of(struct tensor_range, {
      { 0, 0 }, 
      { 0, 1 },
      { 1, 2 },
      { 0, 3 },
    });


  when("providing a vector with current position");
    struct vector position = vector_of(u64, {
      ((struct tensor_range*) vector_get(&positions, 0))->min,
      ((struct tensor_range*) vector_get(&positions, 1))->min,
      ((struct tensor_range*) vector_get(&positions, 2))->min,
      ((struct tensor_range*) vector_get(&positions, 3))->min,
    });


  calling("tensor_iterate()");
  must("correctly iterate all tensor positions");
    void* data_position = NULL;
    u64* current_position = NULL;
    u64 offsets[4] = {
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 0))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 1))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 2))->offset,
      ((struct tensor_dimension*) vector_get(tensor.dimensions, 3))->offset,
    };

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 1*offsets[2] + 1*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 1);
    verify(current_position[3] == 1);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 1*offsets[2] + 2*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 1);
    verify(current_position[3] == 2);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 1*offsets[2] + 3*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 1);
    verify(current_position[3] == 3);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 2*offsets[2] + 0*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 2);
    verify(current_position[3] == 0);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 2*offsets[2] + 1*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 2);
    verify(current_position[3] == 1);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 2*offsets[2] + 2*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 2);
    verify(current_position[3] == 2);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 0*offsets[1] + 2*offsets[2] + 3*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 0);
    verify(current_position[2] == 2);
    verify(current_position[3] == 3);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 1*offsets[2] + 0*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 1);
    verify(current_position[3] == 0);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 1*offsets[2] + 1*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 1);
    verify(current_position[3] == 1);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 1*offsets[2] + 2*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 1);
    verify(current_position[3] == 2);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 1*offsets[2] + 3*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 1);
    verify(current_position[3] == 3);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 2*offsets[2] + 0*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 2);
    verify(current_position[3] == 0);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 2*offsets[2] + 1*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 2);
    verify(current_position[3] == 1);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 2*offsets[2] + 2*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 2);
    verify(current_position[3] == 2);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position != NULL);
    verify((data_position - tensor.data) / sizeof(i32) ==
      0*offsets[0] + 1*offsets[1] + 2*offsets[2] + 3*offsets[3]);
    current_position = position.data;
    verify(current_position[0] == 0);
    verify(current_position[1] == 1);
    verify(current_position[2] == 2);
    verify(current_position[3] == 3);

    data_position = tensor_iterate(&tensor, &positions, &position);
    verify(data_position == NULL);

  success();
    memory_release(&allocator);
}
