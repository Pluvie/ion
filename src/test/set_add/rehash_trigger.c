test( set_add, rehash_trigger ) {

  given("a set");
    set<int>* set = set_alloc(int, 16, test_allocator);
    void* original_set_data = set->data;
    int load_limit = set->load_limit;


  when("the set has some elements in it, under the load limit");
    for (int index = 0; index < load_limit; index++)
      set_add(set, index);


  when("adding a new element and surpassing the load limit");
    int element = 999;


  calling("set_add()");
    set_add(set, element);


  must("trigger the set rehash");
    verify(set->data != original_set_data);
    verify(set->length == load_limit + 1);


  success();
}
