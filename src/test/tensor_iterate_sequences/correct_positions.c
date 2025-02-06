test( tensor_iterate_sequences, correct_positions ) {

  given("a struct tensor");
    struct memory allocator = memory_init(0);
    struct tensor tensor = tensor_init(
      sizeof(i32), &vector_of(u64, { 1, 2, 3, 4 }), &allocator);


  when("providing a vector with sequences");
    struct vector sequences = vector_of(struct sequence, {
      { .values = &vector_of(u64, { 0 }),           .current = 0, .index = 0 }, 
      { .values = &vector_of(u64, { 0, 1 }),        .current = 0, .index = 0 },
      { .values = &vector_of(u64, { 1, 2 }),        .current = 1, .index = 0 },
      { .values = &vector_of(u64, { 0, 1, 2, 3 }),  .current = 0, .index = 0 },
    });


  calling("tensor_iterate_sequences()");
  must("correctly iterate the tensor on all sequences");
    bool next_iteration = false;

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 1);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 2);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 3);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 0);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 1);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 2);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 3);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 0);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 1);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 2);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 3);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 0);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 1);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 2);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == true);
    verify(((struct sequence*) vector_get(&sequences, 0))->current == 0);
    verify(((struct sequence*) vector_get(&sequences, 1))->current == 1);
    verify(((struct sequence*) vector_get(&sequences, 2))->current == 2);
    verify(((struct sequence*) vector_get(&sequences, 3))->current == 3);

    next_iteration = tensor_iterate_sequences(&tensor, &sequences);
    verify(next_iteration == false);


  success();
    memory_release(&allocator);
}
