test( list_alloc, enforce_capacity_pow2 ) {

  given("a list");
    list<int>* list;


  given("an allocator");
    memory allocator = memory_init(0);


  when("the list capacity is not a power of 2");
    int capacity = 33;


  calling("list_alloc()");
    list = list_alloc(int, capacity, &allocator);


  must("enforce the list capacity to the next power of two");
    verify(list->capacity == next_pow2(capacity));


  success();
    memory_release(&allocator);
}
