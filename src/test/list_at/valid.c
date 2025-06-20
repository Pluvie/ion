test( list_at, valid ) {

  given("a list");
    list<int> list = list(int, { 7, 8, 9 });


  when("a position is valid in the list");
    int position = 2;


  calling("list_at()");
    int* element = list_at(&list, position);


  must("return NULL");
    verify(*element == 9);


  success();
}
