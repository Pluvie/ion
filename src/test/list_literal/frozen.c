test( list_literal, frozen ) {

  calling("list_literal()");
    list<int> list = list(int, { 7, 8, 9 });


  must("create a frozen list literal");
    verify(list.length == 3);
    verify(list.length == list.capacity);
    verify(list.length == list.capacity);
    verify(*list_at(&list, 0) == 7);
    verify(*list_at(&list, 1) == 8);
    verify(*list_at(&list, 2) == 9);


  success();
}
