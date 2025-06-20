test( set_alloc, heap_allocated ) {

  given("a set");
    set<int>* set;


  given("an allocator");
    memory allocator = memory_init(0);


  calling("set_alloc()");
    set = set_alloc(int, 64, &allocator);


  must("allocate the set on the heap with corresponding capacity");
    verify(set->allocator == &allocator);
    verify(set->length == 0);
    verify(set->capacity == 64);


  success();
    memory_release(&allocator);
}
