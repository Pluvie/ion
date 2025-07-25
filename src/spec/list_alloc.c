spec( list_alloc ) {

  argument(int capacity);
  argument(memory* allocator);

  precondition("a valid type");
    #define valid_type int

  precondition("a valid allocator")
    allocator = spec_allocator;

  when("the capacity is less than 16") {
    capacity = 12;
    list<int>* list = list_alloc(valid_type, capacity, allocator);

    must("create an empty heap allocated list");
      verify(list->length == 0);
      verify(list->allocator == spec_allocator);

    must("enforce the list capacity to 16");
      verify(list->capacity == 16);

    success();
  } end();

  when("the capacity is greater than 16") {
    capacity = 24;

    must("create an empty heap allocated list");
      list<int>* list = list_alloc(valid_type, capacity, allocator);
      verify(list->length == 0);
      verify(list->allocator == spec_allocator);

    must("enforce the list capacity to the next power of 2 of the given capacity");
      verify(list->capacity == next_pow2(capacity));

    success();
  } end();

  #undef valid_type
  #undef valid_allocator
}
