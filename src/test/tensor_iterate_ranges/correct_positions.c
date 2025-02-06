test( tensor_iterate_ranges, correct_positions ) {

  given("a struct tensor");
    struct memory allocator = memory_init(0);
    struct tensor tensor = tensor_init(
      sizeof(i32), &vector_of(u64, { 1, 2, 3, 4 }), &allocator);


  when("providing a vector with ranges");
    struct vector ranges = vector_of(struct range, {
      { .min = 0, .max = 1, .at = 0, }, 
      { .min = 0, .max = 2, .at = 0, },
      { .min = 1, .max = 3, .at = 1, },
      { .min = 0, .max = 4, .at = 0, },
    });


  calling("tensor_iterate_ranges()");
  must("correctly iterate the tensor on all ranges");
    bool next_iteration = false;

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 1);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 2);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 3);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 0);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 1);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 2);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 0);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 3);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 0);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 1);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 2);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 1);
    verify(((struct range*) vector_get(&ranges, 3))->at == 3);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 0);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 1);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 2);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == true);
    verify(((struct range*) vector_get(&ranges, 0))->at == 0);
    verify(((struct range*) vector_get(&ranges, 1))->at == 1);
    verify(((struct range*) vector_get(&ranges, 2))->at == 2);
    verify(((struct range*) vector_get(&ranges, 3))->at == 3);

    next_iteration = tensor_iterate_ranges(&tensor, &ranges);
    verify(next_iteration == false);


  success();
    memory_release(&allocator);
}
