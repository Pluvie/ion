test( set_has, present ) {

  given("a set");
    set<int> set = set(int, { 7, 8, 9 });


  when("an element is present in the set");
    int element = 8;


  calling("set_has()");
    bool presence = set_has(&set, element);


  must("return true");
    verify(presence == true);


  success();
}
