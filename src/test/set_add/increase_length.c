test( set_add, increase_length ) {

  given("a set");
    set<int> set = set_init(int, 16);


  calling("set_add()");
    set_add(&set, 7);
    set_add(&set, 8);
    set_add(&set, 9);


  must("increase the set length");
    verify(set.length == 3);


  success();
}
