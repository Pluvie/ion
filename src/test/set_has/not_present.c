test( set_has, not_present ) {

  given("a set");
    set<int> set = set(int, { 7, 8, 9 });


  when("an element is not present in the set");
    int element = 5;


  calling("set_has()");
    bool presence = set_has(&set, element);


  must("return false");
    verify(presence == false);


  success();
}
