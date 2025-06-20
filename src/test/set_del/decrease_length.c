test( set_del, decrease_length ) {

  given("a set");
    set<int>* set = set_alloc(int, 16, test_allocator);
    set_add(set, 7);
    set_add(set, 8);
    set_add(set, 9);
    verify(set->length == 3);


  when("an element is present in the set");
    int element = 8;


  calling("set_del()");
    int position = set_del(set, element);


  must("decrease the set length");
    verify(position >= 0);
    verify(set->length == 2);


  success();
}
