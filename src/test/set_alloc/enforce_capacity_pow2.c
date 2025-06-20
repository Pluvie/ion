test( set_alloc, enforce_capacity_pow2 ) {

  given("a set");
    set<int>* set;


  given("an allocator");
    memory allocator = memory_init(0);


  when("the set capacity is not a power of 2");
    int capacity = 33;


  calling("set_alloc()");
    set = set_alloc(int, capacity, &allocator);


  must("enforce the set capacity to the next power of two");
    verify(set->capacity == next_pow2(capacity));


  success();
    memory_release(&allocator);
}
