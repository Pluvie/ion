test( list_push, copy_element ) {

  given("a list");
    list<int> list = list_init(int, 16);


  calling("list_push()");
    list_push(&list, 7);
    list_push(&list, 8);


  must("copy the element on the list data");
    verify(*(list.data + 0) == 7);
    verify(*(list.data + 1) == 8);


  success();
}
