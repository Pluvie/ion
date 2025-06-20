test( list_push, increase_length ) {

  given("a list");
    list<int> list = list_init(int, 16);
    verify(list.length == 0);


  calling("list_push()");
    list_push(&list, 7);
    list_push(&list, 8);


  must("increase the list length");
    verify(list.length == 2);


  success();
}
