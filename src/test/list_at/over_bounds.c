test( list_at, over_bounds ) {

  given("a list");
    list<int> list = list(int, { 7, 8, 9 });


  when("a position is over the bounds of the list");
    int position = 5;


  calling("list_at()");
    int* element = list_at(&list, position);


  must("return NULL");
    verify(element == NULL);


  success();
}
