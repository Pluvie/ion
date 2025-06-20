test( set_pos, not_present ) {

  given("a set");
    set<int> set = set(int, { 7, 8, 9 });


  when("an element is not present in the set");
    int element = 5;


  calling("set_pos()");
    int position = set_pos(&set, element);


  must("return -1");
    verify(position == -1);


  success();
}
