spec( set_rehash ) {

  argument(set<char*>* set);

  precondition("a heap allocated set");
    #define preconditions \
      set = set_alloc(char*, 8, spec_allocator); \
      set_add(set, "a"); \
      set_add(set, "b"); \
      set_add(set, "c");

  apply(preconditions);
  int original_set_length = set->length;
  int original_set_capacity = set->capacity;
  set_rehash(set);

  must("not fail");
    verify(failure.occurred == false);

  must("keep the elements in the set");
    verify(set_has(set, "a") == true);
    verify(set_has(set, "b") == true);
    verify(set_has(set, "c") == true);

  must("leave the set length unchanged");
    verify(set->length == original_set_length);

  must("increase the set capacity by a factor 2");
    verify(set->capacity == 2*original_set_capacity);

  success();

  #undef preconditions
}
