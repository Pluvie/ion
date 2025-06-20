test( set_del, invariance_on_missing ) {

  given("a set");
    set<int>* set = set_alloc(int, 16, test_allocator);
    set_add(set, 7);
    set_add(set, 8);
    set_add(set, 9);
    verify(set->length == 3);


  when("an element is not present in the set");
    int element = 10;


  calling("set_del()");
    int position = set_del(set, element);


  must("not change the set length");
    verify(position == -1);
    verify(set->length == 3);


  success();
}
