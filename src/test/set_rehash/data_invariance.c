test( set_rehash, data_invariance ) {

  given("a set");
    set<int>* set = set_alloc(int, 16, test_allocator);
    void* original_set_data = set->data;


  when("the set has some elements in it");
    set_add(set, 7);
    set_add(set, 8);
    set_add(set, 9);


  calling("set_rehash()");
    set_rehash(set);


  must("be invariant on the set elements");
    verify(set->data != original_set_data);
    verify(set->length == 3);
    verify(set_has(set, 7));
    verify(set_has(set, 8));
    verify(set_has(set, 9));


  success();
}
