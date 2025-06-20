test( set_add, occupy_pos ) {

  given("a set");
    set<int> set = set_init(int, 16);


  calling("set_add()");
    int position = set_add(&set, 7);


  must("return and occupy the set hashes position");
    verify(position >= 0);
    for (int i = 0; i < set.capacity; i++) {
      if (i == position) {
        verify(set_pos_is_occupied(&set, i));
      } else {
        verify(set_pos_is_free(&set, i));
      }
    }


  success();
}
