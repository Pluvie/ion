test( set_alloc, enforce_capacity ) {

  given("a set");
    set<int>* set;


  given("an allocator");
    memory allocator = memory_init(0);


  when("the set capacity is inferior to 16");
    int capacity = 9;


  calling("set_alloc()");
    set = set_alloc(int, capacity, &allocator);


  must("enforce the set capacity to 16");
    verify(set->capacity == 16);


  success();
    memory_release(&allocator);
}
