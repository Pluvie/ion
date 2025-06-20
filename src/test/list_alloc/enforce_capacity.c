test( list_alloc, enforce_capacity ) {

  given("a list");
    list<int>* list;


  given("an allocator");
    memory allocator = memory_init(0);


  when("the list capacity is inferior to 16");
    int capacity = 9;


  calling("list_alloc()");
    list = list_alloc(int, capacity, &allocator);


  must("enforce the list capacity to 16");
    verify(list->capacity == 16);


  success();
    memory_release(&allocator);
}
