spec( set_alloc ) {

  argument(int capacity);
  argument(memory* allocator);

  precondition("a valid type");
    #define valid_type int

  precondition("a valid allocator")
    allocator = spec_allocator;

  when("the capacity is less than 16") {
    capacity = 12;
    set<int>* set = set_alloc(valid_type, capacity, allocator);

    must("create an empty heap allocated set");
      verify(set->length == 0);
      verify(set->allocator == spec_allocator);

    must("enforce the set capacity to 16");
      verify(set->capacity == 16);

    success();
  } end();

  when("the capacity is greater than 16") {
    capacity = 24;

    must("create an empty heap allocated set");
      set<int>* set = set_alloc(valid_type, capacity, allocator);
      verify(set->length == 0);
      verify(set->allocator == spec_allocator);

    must("enforce the set capacity to the next power of 2 of the given capacity");
      verify(set->capacity == next_pow2(capacity));

    success();
  } end();

  #undef valid_type
  #undef valid_allocator
}
