test( set_pos, present ) {

  given("a set");
    set<int> set = set(int, { 7, 8, 9 });


  when("an element is present in the set");
    int element = 8;


  calling("set_pos()");
    int position = set_pos(&set, element);


  must("return the element position in the set");
    verify(position == 1);


  success();
}
