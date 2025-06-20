test( set_pos, free ) {

  given("a set");
    set<int> set = set(int, { 7, 8, 9 });


  when("an element was deleted from the set");
    set_del(&set, 9);


  calling("set_pos()");
    int position = set_pos(&set, 9);


  must("return the element position in the set");
    verify(position == 2);


  success();
}
