test( list_alloc, heap_allocated ) {

  given("a list");
    list<int>* list;


  given("an allocator");
    memory allocator = memory_init(0);


  calling("list_alloc()");
    list = list_alloc(int, 64, &allocator);


  must("allocate the list on the heap with corresponding capacity");
    verify(list->allocator == &allocator);
    verify(list->length == 0);
    verify(list->capacity == 64);


  success();
    memory_release(&allocator);
}
