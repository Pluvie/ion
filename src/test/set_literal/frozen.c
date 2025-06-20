test( set_literal, frozen ) {

  calling("set_literal()");
    set<int> set = set(int, { 7, 8, 9 });


  must("create a frozen set literal");
    verify(set.length == 3);
    verify(set.length == set.capacity);
    verify(set.length == set.load_limit);
    verify(set_has(&set, 7) == true);
    verify(set_has(&set, 8) == true);
    verify(set_has(&set, 9) == true);


  success();
}
