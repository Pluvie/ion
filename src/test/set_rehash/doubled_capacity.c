test( set_rehash, doubled_capacity ) {

  given("a set");
    set<int>* set = set_alloc(int, 16, test_allocator);
    int original_set_capacity = set->capacity;


  when("the set has some elements in it");
    set_add(set, 7);
    set_add(set, 8);
    set_add(set, 9);


  calling("set_rehash()");
    set_rehash(set);


  must("double the set capacity");
    verify(set->capacity == original_set_capacity * 2);
    verify(set->length == 3);
    verify(set_has(set, 7));
    verify(set_has(set, 8));
    verify(set_has(set, 9));


  success();
}
