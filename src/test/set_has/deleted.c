test( set_has, deleted ) {

  given("a set");
    set<int> set = set(int, { 7, 8, 9 });


  when("an element is deleted from the set");
    int element = 8;
    set_del(&set, element);


  calling("set_has()");
    bool presence = set_has(&set, element);


  must("return false");
    verify(presence == false);


  success();
}
